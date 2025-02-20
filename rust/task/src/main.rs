use std::io;
fn main() {
    //let a = [1,2,3,4,5];

    // println!("Please enter an array index.");

    // let mut index = String::new();

    // io::stdin().read_line(&mut index).expect("Failed to read line.");

    // let index : usize = index.trim().parse().expect("Index must be a number.");

    // let element = a[index];
    // println!("{element}")
    //task_1();
    //task_2();
    //println!("{}", five());

    //print!(
    //    "{}",
    //    f({
    //        let y = 1;
    //        y + 1
    //    })
    //);
    //counter_loop();
    //two_loop();
    // sum_function();
    // task_number1();
    //srednee_arefmiticheskoe();
    //proverca_zadachi();
    //tretiy_lishniy();
    converter_function();
}
/// task_1 creates an array of 100 strings, each of which is
/// "This temperature is: ". The first and second elements
/// of the array are then printed, separated by a comma.
#[warn(dead_code)]
fn task_1() {
    let messages = "This temperature is: ";
    let x = [messages; 100];
    println!("{},{}", x[0], x[1]);
}
/// Creates a tuple of two arrays, the first of which has length 2 and contains
/// all 1s, and the second of which has length 4 and contains all 3s.
/// Then, it extracts the first element of the first array and the first element
/// of the second array, and prints their sum.
#[warn(dead_code)]
fn task_2() {
    let t = ([1; 2], [3; 4]);
    let (a, b) = t;

    println!("{}", a[0] + t.1[0]);
}
/// Returns the number 5.
#[warn(dead_code)]
fn five() -> i32 {
    5
}
/// Increments the input integer by 1 and returns the result.
///
/// # Arguments
///
/// * `x` - An integer input.
///
/// # Returns
///
/// * An integer that is one greater than the input `x`.

#[warn(dead_code)]
fn f(x: i32) -> i32 {
    x + 1
}
/// A loop that increments a counter until it reaches 10, then returns the doubled count.
/// The doubled count is then printed to the console.
#[warn(dead_code)]
fn counter_loop() {
    let mut count: i32 = 0;

    let result = loop {
        count += 1;

        if count == 10 {
            break count * 2;
        }
    };
    println!("{}", result)
}

/// This function shows how to use nested loops and labels to control the flow of a program.
///
/// The outer loop will continue to run until the value of `count` is 2.
/// The inner loop will run until the value of `remaining` is 9.
///
/// The output of the program will be:
/// count= 0
/// remaining= 10
/// remaining= 9
/// count= 1
/// remaining= 10
/// remaining= 9
/// End count= 2
#[warn(dead_code)]
fn two_loop() {
    let mut count = 0;
    'counting_up: loop {
        print!("count= {count}");
        let mut remaining = 10;

        loop {
            println!("remaining= {remaining}");
            if remaining == 9 {
                break;
            }
            if count == 2 {
                break 'counting_up;
            }
            remaining -= 1;
        }
        count += 1;
    }
    println!("End count= {count}");
}

/// Reads two numbers from the standard input and prints their sum.
/// The result is a 64-bit integer.
///
/// # Example
///
///
#[warn(dead_code)]
fn sum_function() {
    let mut number1 = String::new();
    let mut number2 = String::new();

    io::stdin().read_line(&mut number1).unwrap();
    io::stdin().read_line(&mut number2).unwrap();

    let result: i64 =
        number1.trim().parse::<i64>().unwrap() + number2.trim().parse::<i64>().unwrap();
    println!("{}", result);
}

/// This function takes two numbers and prints the result of multiplying
/// the first number by all integers from 1 to 10, then the second number
/// by all integers from 1 to 10.
#[warn(dead_code)]
fn task_number1() {
    let mut number_1 = String::new();
    let mut number_2 = String::new();

    io::stdin().read_line(&mut number_1).expect("Failed to read line.");
    let a: i32 = number_1.trim().parse().expect("Failed to parse number.");

    io::stdin().read_line(&mut number_2).expect("Failed to read line.");
    let b: i32 = number_2.trim().parse().expect("Failed to parse number.");

    for i in 1..=10 {
        println!("{} x {} = {}", a, i, a * i);
    }
    println!("");

    for i in 1..=10 {
        println!("{} x {} = {}", b, i, b * i);
    }
}

/// This function reads two integers from the standard input and calculates
/// the remainder of the division of the first number by the second.
/// It then prints the result in a formatted message indicating the available
/// square meters of free space.

#[warn(dead_code)]
fn ostatok_ot_delenia() {
    let mut number_1 = String::new();
    let mut number_2 = String::new();

    io::stdin().read_line(&mut number_1).expect("Failed to read line.");
    let a: i32 = number_1.trim().parse().expect("Failed to parse number.");

    io::stdin().read_line(&mut number_2).expect("Failed to read line.");
    let b: i32 = number_2.trim().parse().expect("Failed to parse number.");

    println!("На поле доступно еще {} кв.м свободного места", a % b);
}

/// This function takes two numbers and prints the result of arithmetic operations
/// of addition, subtraction, multiplication, division, and remainder.
#[warn(dead_code)]
fn srednee_arefmiticheskoe() {
    let mut number_1 = String::new();
    let mut number_2 = String::new();

    io::stdin().read_line(&mut number_1).expect("Failed to read line.");
    let a: i32 = number_1.trim().parse().expect("Failed to parse number.");

    io::stdin().read_line(&mut number_2).expect("Failed to read line.");
    let b: i32 = number_2.trim().parse().expect("Failed to parse number.");

    println!("{} + ({}) = {}", a, b, a + b);
    println!("{} - ({}) = {}", a, b, a - b);
    println!("{} * ({}) = {}", a, b, a * b);
    println!("{} / ({}) = {}", a, b, a / b);
    println!("{} % ({}) = {}", a, b, a % b);
}

/// This function reads two numbers from the standard input, then prints the
/// second number first, followed by the first number.
fn tretiy_lishniy() {
    let mut number_1 = String::new();
    let mut number_2 = String::new();

    io::stdin().read_line(&mut number_1).expect("Failed to read text ");
    let a: i32 = number_1.trim().parse().expect("Failed to parse number");
    io::stdin().read_line(&mut number_2).expect("Failed to read line");
    let b: i32 = number_2.trim().parse().expect("Failed to parse number");

    println!("{}", b);
    println!("{}", a);
}

fn converter_function() {
    let mut input_number_1 = String::new();

    io::stdin().read_line(&mut input_number_1).expect("Failed to read line");
    let a: i32 = input_number_1.trim().parse().expect("Failed to parse number");

    println!("{:#b}", a);
    println!("{:#o}", a);
    println!("{:#x}", a);
}
