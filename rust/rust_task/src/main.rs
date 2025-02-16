use std::io;
fn main() {
    println!("{}", add(1, 2));
    sum_number();
}

fn add(left: usize, right: usize) -> usize {
    left + right
}

fn sum_number() {
    let mut number1 = String::new();
    let mut number2 = String::new();

    io::stdin().read_line(&mut number1).expect("Error");
    io::stdin().read_line(&mut number2).expect("Error");

    let number1: i32 = number1.trim().parse().unwrap();
    let number2: i32 = number2.trim().parse().unwrap();

    println!("{}", number1 + number2);
}
