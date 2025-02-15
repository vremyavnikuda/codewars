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
    sum_function();
}
#[warn(dead_code)]
fn task_1() {
    let messages = "This temperature is: ";
    let x = [messages; 100];
    println!("{},{}", x[0], x[1]);
}
#[warn(dead_code)]
fn task_2() {
    let t = ([1; 2], [3; 4]);
    let (a, b) = t;

    println!("{}", a[0] + t.1[0]);
}
#[warn(dead_code)]
fn five() -> i32 {
    5
}
#[warn(dead_code)]
fn f(x: i32) -> i32 {
    x + 1
}
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

fn sum_function() {
    let mut number1 = String::new();
    let mut number2 = String::new();

    io::stdin().read_line(&mut number1).unwrap();
    io::stdin().read_line(&mut number2).unwrap();

    let result: i64 =
        number1.trim().parse::<i64>().unwrap() + number2.trim().parse::<i64>().unwrap();
    println!("{}", result);
}
