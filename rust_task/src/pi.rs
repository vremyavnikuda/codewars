//const pi:f32=3.14159;
//fn main(){
//    println!("To make an apple {} from scratch, you must first create a universe.",pi);
//}
fn main(){
    task1();
    let result= swap(123, 321);
    println!("{} {}",result.0,result.1);
}

use std::f32;
use std::env;

const  PI :f32 = f32::consts::PI+f32::consts::PI;

pub fn task1() {
    println!("Число эйлера: {}", f32::consts::E);
    println!("Полный оборот тригонометрической окружности: {}", PI);
    println!("Архитектура процессора на платформе: {}", env::consts::ARCH);
    println!("ОС на платформе: {}", env::consts::OS);
}



fn sum(x:i32,y:i32) -> i32{
    x+y
}
fn print() -> (){
    println!("Success!");
}

fn call_me(number:i64)->(){
    println!("Звоню! Вызываемый номер {}",number)
}

fn swap(x:i32,y:i32)->(i32,i32){
    (y,x)
}