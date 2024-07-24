use std::io;

pub mod task;
pub mod are_you_playing_banjo;
mod task2;
mod cockroach_speed;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let mut expect = input.split_whitespace();

    let a:i32=expect.next().expect("Please enter two numbers").parse().expect("Please type a number!");
    let b:i32=expect.next().expect("Please enter two numbers").parse().expect("Please type b number!");
    let c:i32 =expect.next().expect("Please enter two numbers").parse().expect("Please type c number!");
    if a+b>c && a+c>b && b+c>a{
        println!("Существует");
    }else {
        println!("Не существует");
    }
}

fn input_integer() -> String {
    let mut input_string = String::new();

    std::io::stdin().read_line(&mut input_string).expect("Failed to read line");

    let x: i32 = match input_string.trim().parse() {
        Ok(num) => num,
        Err(_) => panic!("Invalid input"),
    };

    let result = x * 2 + 100;
    return format!("{}", result);
}
