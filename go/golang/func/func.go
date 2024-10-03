package _func

import "fmt"


func minimumFromFour() int{
	var num1,num2,num3,num4 int
	fmt.Scan(&num1,&num2,&num3,&num4)
	result := min(num1, num2, num3, num4)
	fmt.Println(result)
	return result
}
func main(){
	minimumFromFour()
}