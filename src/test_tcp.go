// TCP test code

package main

import (
	"fmt"
	"net/http"
)

func main() {
	fmt.Println("TCP test")
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		fmt.Fprintf(w, "Hello, TCP!")
	})
	http.ListenAndServe(":8080", nil)
	// 这个就是一个最典型的示例，创建了一个HTTP服务器，监听8080端口，当访问根路径时返回"Hello, TCP!"。这个示例展示了如何使用Go语言的net/http包来创建一个简单的TCP服务器。
}
