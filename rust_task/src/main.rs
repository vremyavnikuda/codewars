use std::io;

pub mod are_you_playing_banjo;
mod bool_to_word;
mod cockroach_speed;
mod disemvowel;
mod goroda;
mod hate_school;
mod last_text;
mod parse_url;
pub mod task;
mod task2;
mod upper_age;
mod vec_user;
mod remove_ever_other;

fn main() {
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");
    let mut expect = input.split_whitespace();

    let a: i32 = expect
        .next()
        .expect("Please enter two numbers")
        .parse()
        .expect("Please type a number!");
    let b: i32 = expect
        .next()
        .expect("Please enter two numbers")
        .parse()
        .expect("Please type b number!");
    let c: i32 = expect
        .next()
        .expect("Please enter two numbers")
        .parse()
        .expect("Please type c number!");
    if a + b > c && a + c > b && b + c > a {
        println!("Существует");
    } else {
        println!("Не существует");
    }
}
#[allow(unused)]
fn input_integer() -> String {
    let mut input_string = String::new();

    std::io::stdin()
        .read_line(&mut input_string)
        .expect("Failed to read line");

    let x: i32 = match input_string.trim().parse() {
        Ok(num) => num,
        Err(_) => panic!("Invalid input"),
    };

    let result = x * 2 + 100;
    return format!("{}", result);
}
