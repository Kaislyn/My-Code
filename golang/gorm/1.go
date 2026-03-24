package main

import (
  "gorm.io/driver/mysql"
  "gorm.io/gorm"
  "gorm.io/gorm/logger"
  "time"
)

// 全局DB对象（项目中推荐单例）
var db *gorm.DB

func initDB() {
  // 1. 拼接DSN（MySQL连接字符串，你熟悉的格式）
  // 用户名:密码@tcp(IP:端口)/数据库名?charset=utf8mb4&parseTime=True&loc=Local
  dsn := "root:123456@tcp(127.0.0.1:3306)/test_gorm?charset=utf8mb4&parseTime=True&loc=Local"

  // 2. 连接数据库 + 配置
  db, err := gorm.Open(mysql.Open(dsn), &gorm.Config{
    // 打印执行的SQL（开发必备，对比原生SQL）
    Logger: logger.Default.LogMode(logger.Info),
  })
  if err != nil {
    panic("连接数据库失败：" + err.Error())
  }

  // 3. 配置连接池（MySQL优化必备）
  sqlDB, err := db.DB()
  if err != nil {
    panic(err)
  }
  sqlDB.SetMaxIdleConns(10)   // 空闲连接数
  sqlDB.SetMaxOpenConns(100)  // 最大连接数
  sqlDB.SetConnMaxLifetime(time.Hour) // 连接最长存活时间
}

func main() {
  initDB()
  println("数据库连接成功！")
}