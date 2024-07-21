use std::io;

fn main() {
    hello_world();
    human_id("Andrew", 33, 182.1);
    let _x: i32 = {
        let price = 5;
        let qty = 10;
        price * qty
    };
    println!("Result:{}", _x);
    println!("{}", add(1, 2));
    let y = add(4,5);
    println!("Value of y is : {}",y);
    println!("Value from function 'add' is: {}",add(4,5));

    // Calling function BMI
    let bmi=calculate_bmi(71.1, 1.83);
    println!("My index BMI {:.3}",bmi);
    //sum_numbers();
    //number_revers();
    medium_number();
}

fn hello_world() {
    println!("Hello, World!");
}
fn human_id(name: &str, age: i32, height: f32) {
    println!(
        "Мое имя : {} мне {} лет и мой рост {} см",
        name, age, height
    );
}

fn add(a: i32, b: i32) -> i32 {
    a + b
}

// BMI= height(kg)/height(m)^2
fn calculate_bmi(weight_kg:f64, height_m:f64) -> f64 {
    weight_kg/(height_m*height_m )
}
//дано трехзначное число,найти сумму его цифр.
//на вход дается трехзначное число
//вывести одно целое число -> сумма цифр введенного числа
fn sum_numbers(){
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");

    // Convert the input string to an integer
    let number:i32=input.trim().parse().expect("Not a number");
    let mut sum=0;
    let mut num=number;

    while num!=0{
        sum+=num%10;
        num/=10;
    }
    println!("{}",sum);
}


//Revers number function
fn number_revers(){
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");

    // TODO: reverse the number
    let reversed = input.chars().rev().collect::<String>();

    println!("{}", reversed);
}

//Функция для вычисления среднего значения двух чисел
fn medium_number(){
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");

    let mut iter = input.split_whitespace();
    let a: i32 = iter.next().expect("Please enter two numbers").parse().expect("Please type a number!");
    let b: i32 = iter.next().expect("Please enter two numbers").parse().expect("Please type a number!");

    let sum = a + b;
    let average = sum as f32 / 2.0;

    if sum % 2 == 0 {
        println!("{}", sum / 2);
    } else {
        println!("{:.1}", average);
    }
}

