Go 单例模式（饿汉式 / 懒汉式）超详细讲解（新手友好）
文档说明
本文基于新手视角，用「大白话 + 生活例子」拆解 Go 语言单例模式的两种实现方式，同时解答并发、执行顺序、测试等核心疑问，适合 0 基础理解。
目录
单例模式核心概念
饿汉式实现（提前创建）
懒汉式实现（按需创建）
单元测试 & 基准测试解读
常见问题解答（锁 / 通道、Go 执行顺序）
核心总结
1. 单例模式核心概念
一句话定义：让一个结构体在程序运行期间，只能创建「唯一一个实例对象」，避免多实例导致的配置不一致、资源浪费等问题。
生活例子：家里的电表箱（整套房只有 1 个）、程序中的配置管理器 / 日志管理器（只需要 1 个）。
2. 饿汉式实现（提前创建）
2.1 核心逻辑
“饿汉”= 迫不及待，程序一启动就创建实例（无需手动调用，早于 main 函数），简单无并发问题，但可能浪费资源（实例不用也会创建）。
2.2 完整代码
go
运行
package singleton

// Singleton 定义单例结构体（空结构体即可，重点是实例唯一）
type Singleton struct{}

// 全局变量：存储唯一实例（初始为nil）
var singleton *Singleton

// init函数：程序启动、包加载时自动执行（早于main）
func init() {
    // 程序启动就创建实例，赋值给全局变量
    singleton = &Singleton{}
}

// GetInstance 对外提供获取实例的函数
func GetInstance() *Singleton {
    // 直接返回提前创建好的实例
    return singleton
}
2.3 关键特点
创建时机：包初始化阶段（init 函数），早于 main 函数，无需手动调用；
优点：代码简单、无并发安全问题（实例提前创建，所有调用者拿同一个）；
缺点：若实例占内存大但全程未使用，会浪费资源。
3. 懒汉式实现（按需创建）
3.1 核心逻辑
“懒汉”= 能偷懒就偷懒，只有第一次调用获取实例的函数时，才创建实例，后续调用直接返回已创建的实例，节省资源，但需处理并发安全。
3.2 生活例子
懒汉式妈妈：早上不摆零食柜，等你第一次喊 “要吃零食” 才摆；后续再喊，直接指已摆好的零食柜（绝不摆第二个）；若永远不喊，就永远不摆。
3.3 完整代码
go
运行
package singleton

import "sync"

// 全局变量：存储懒汉式实例（初始为nil）
var (
    lazySingleton *Singleton
    // sync.Once：Go标准库工具，保证内部函数只执行1次（解决并发问题）
    once          = &sync.Once{}
)

// GetLazyInstance 对外提供获取懒汉式实例的函数
func GetLazyInstance() *Singleton {
    // 第一步：检查实例是否未创建（nil）
    if lazySingleton == nil {
        // 第二步：sync.Once保证匿名函数只执行1次（哪怕多goroutine同时调用）
        once.Do(func() {
            // 仅第一次调用时创建实例
            lazySingleton = &Singleton{}
        })
    }
    // 返回实例（第一次是新创建的，后续是同一个）
    return lazySingleton
}
3.4 关键细节（新手必懂）
sync.Once 不是普通锁，但底层用互斥锁实现；核心作用是「让内部函数只执行 1 次」，避免多 goroutine 同时创建多个实例；
对比普通锁：普通锁（sync.Mutex）每次调用都要 “加锁 / 解锁”，性能差；sync.Once 仅第一次调用加锁，后续直接跳过，性能更优；
通道实现：也能用通道实现 “只创建 1 次”，但代码复杂（杀鸡用牛刀），sync.Once 是 Go 官方推荐的最优解。
3.5 懒汉式特点
创建时机：第一次调用GetLazyInstance()时；若不调用，实例永远不创建；
优点：节省资源（不用不创建）；
缺点：需用sync.Once保证并发安全，代码比饿汉式稍复杂，性能略差。
4. 单元测试 & 基准测试解读
4.1 单元测试（验证单例 “唯一性”）
作用：验证每次调用获取实例的函数，返回的都是同一个实例。
测试文件命名：必须为xxx_test.go（如singleton_test.go）；
测试函数规则：以Test开头，参数为*testing.T；
第三方库：github.com/stretchr/testify/assert（断言库，简化 “相等判断”）。
4.1.1 完整测试代码
go
运行
package singleton_test

import (
    "testing"
    singleton "github.com/mohuishou/go-design-pattern/01_singleton"
    "github.com/stretchr/testify/assert"
)

// 测试饿汉式实例唯一性
func TestGetInstance(t *testing.T) {
    ins1 := singleton.GetInstance()
    ins2 := singleton.GetInstance()
    // 断言：两个实例必须相等（指向同一个对象），否则测试失败
    assert.Equal(t, ins1, ins2)
}

// 测试懒汉式实例唯一性
func TestGetLazyInstance(t *testing.T) {
    ins1 := singleton.GetLazyInstance()
    ins2 := singleton.GetLazyInstance()
    assert.Equal(t, ins1, ins2)
}
4.2 基准测试（对比性能）
作用：测试高并发场景下，两种单例模式的执行效率。
基准函数规则：以Benchmark开头，参数为*testing.B；
b.RunParallel：模拟多 goroutine 并发调用（贴近真实场景）。
4.2.1 完整基准测试代码
go
运行
// 测试饿汉式并发性能
func BenchmarkGetInstanceParallel(b *testing.B) {
    b.RunParallel(func(pb *testing.PB) {
        // pb.Next()：循环执行，直到基准测试结束
        for pb.Next() {
            if singleton.GetInstance() != singleton.GetInstance() {
                b.Errorf("测试失败：实例不唯一")
            }
        }
    })
}

// 测试懒汉式并发性能
func BenchmarkGetLazyInstanceParallel(b *testing.B) {
    b.RunParallel(func(pb *testing.PB) {
        for pb.Next() {
            if singleton.GetLazyInstance() != singleton.GetLazyInstance() {
                b.Errorf("测试失败：实例不唯一")
            }
        }
    })
}
4.2.2 测试结果解读
plaintext
// 懒汉式：每次调用耗时2.24纳秒，执行5.35亿次
BenchmarkGetLazyInstanceParallel-4      535702941                2.24 ns/op           
// 饿汉式：每次调用耗时0.586纳秒，执行10亿次（性能更好）
BenchmarkGetInstanceParallel-4          1000000000               0.586 ns/op          
核心指标：
ns/op：每次调用耗时（纳秒），数值越小性能越好；
执行次数：次数越多，性能越好；
结论：饿汉式性能优于懒汉式（无额外判断 / 锁检测）。
5. 常见问题解答
5.1 饿汉式 “程序启动就创建”= main 函数里直接调用？
❌ 不是！Go 程序执行顺序：
plaintext
程序启动 → 加载包 → 初始化全局变量 → 执行init函数 → 执行main函数
饿汉式的实例创建在init函数中，早于 main 函数，哪怕 main 函数不调用GetInstance()，实例也会创建。
5.2 为什么懒汉式不用通道，而用sync.Once？
通道核心场景：goroutine 之间传数据、同步执行顺序（如生产者 - 消费者）；
sync.Once：专门解决 “操作只执行 1 次”，代码简单、性能优；
通道实现单例：可行但代码复杂（杀鸡用牛刀），不推荐。
5.3 Go 代码 “书写顺序≠执行顺序”？
核心规则：
包级代码（全局变量、init 函数）：先初始化全局变量 → 执行 init 函数（早于 main）；
函数内代码：从上到下执行（无分支 / 循环时）；
函数定义（如func xxx()）：仅 “声明”，不执行，只有被调用时才执行。
6. 核心总结
表格
类型	创建时机	优点	缺点	并发安全
饿汉式	程序启动（init 函数）	简单、性能好	可能浪费资源	✅ 天然安全
懒汉式	第一次调用 GetLazyInstance	节省资源	代码稍复杂、性能略差	✅ 需 sync.Once 保证
核心共性	均保证实例唯一	-	-	-
为什么复制后看不到 Markdown 格式效果？（快速解决）
第一步：确保文件后缀是.md
你需要在 VSCode 中新建文件，命名为singleton_note.md（必须以.md结尾），再把笔记复制进去 —— 如果后缀是.txt或.go，只会显示纯文本，不会渲染 MD 格式。
第二步：打开 VSCode 的 Markdown 预览
复制笔记到.md文件后，按快捷键Ctrl+Shift+V（Windows/Linux）或Cmd+Shift+V（Mac），会弹出 “Markdown 预览窗口”，此时就能看到格式化的标题、代码块、表格等效果。
第三步：检查复制完整性
确保复制时包含所有 Markdown 语法（如#标题、```代码块、| 表格 |`），如果复制时漏掉语法符号，也会显示异常。
总结
单例模式核心是「实例唯一」，饿汉式提前创建、懒汉式按需创建；
懒汉式用sync.Once保证并发安全，是 Go 最优解；
复制后看不到 MD 效果，核心是文件后缀要为.md+ 打开预览窗口；
单元测试验证单例唯一性，基准测试对比性能，饿汉式性能更优。