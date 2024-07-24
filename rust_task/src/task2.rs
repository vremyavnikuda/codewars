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
    let y = add(4, 5);
    println!("Value of y is : {}", y);
    println!("Value from function 'add' is: {}", add(4, 5));

    // Calling function BMI
    let bmi = calculate_bmi(71.1, 1.83);
    println!("My index BMI {:.3}", bmi);
    //sum_numbers();
    //number_revers();
    // medium_number();
    //katet();
    // triangle_exists();
    // electric_clock();
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
fn calculate_bmi(weight_kg: f64, height_m: f64) -> f64 {
    weight_kg / (height_m * height_m)
}
//дано трехзначное число,найти сумму его цифр.
//на вход дается трехзначное число
//вывести одно целое число -> сумма цифр введенного числа
fn sum_numbers() {
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");

    // Convert the input string to an integer
    let number: i32 = input.trim().parse().expect("Not a number");
    let mut sum = 0;
    let mut num = number;

    while num != 0 {
        sum += num % 10;
        num /= 10;
    }
    println!("{}", sum);
}

//Revers number function
fn number_revers() {
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");

    // TODO: reverse the number
    let reversed = input.chars().rev().collect::<String>();

    println!("{}", reversed);
}

//Функция для вычисления среднего значения двух чисел
fn medium_number() {
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");

    let mut iter = input.split_whitespace();
    let a: i32 = iter
        .next()
        .expect("Please enter two numbers")
        .parse()
        .expect("Please type a number!");
    let b: i32 = iter
        .next()
        .expect("Please enter two numbers")
        .parse()
        .expect("Please type a number!");

    let sum = a + b;
    let average = sum as f32 / 2.0;

    if sum % 2 == 0 {
        println!("{}", sum / 2);
    } else {
        println!("{:.1}", average);
    }
}

// функция которая считывает длины двух катетов в прямоугольном треугольнике и выводит его площадь
fn katet() {
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");
    let mut iter = input.split_whitespace();

    let a: i32 = iter
        .next()
        .expect("Please enter two numbers")
        .parse()
        .expect("Please type a number!");
    let b: i32 = iter
        .next()
        .expect("Please enter two numbers")
        .parse()
        .expect("Please type b number!");

    let result = a + b;
    println!("{}", result);
}

// Даны три натуральный числа a, b, c
// Определить ,существует ли треугольник с такими сторонами
fn triangle_exists() {
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");
    let mut exists = input.split_whitespace();

    let _a: i32 = exists.next().expect("INFO").parse().expect("Error");
    let _b: i32 = exists.next().expect("INFO").parse().expect("Error");
    let _c: i32 = exists.next().expect("INFO").parse().expect("Error");

    if _a + _b > _c && _a + _c > _b && _b + _c > _a {
        println!("{}", true)
    } else {
        println!("{}", false)
    }
}

//Вывести часы:минуты:секунды из N числа
fn electric_clock() {
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");
    let mut n = input.split_whitespace();

    //Переводим N в целое число
    let _n: i32 = n.next().expect("INFO").parse().expect("ERROR");

    //переводим число n в часы:минуты:секунды
    let _total_seconds = _n % 86400;
    let hours = _total_seconds / 3600;
    let minutes = (_total_seconds % 3600) / 60;
    let seconds = _total_seconds % 60;

    println!("{}:{:02}:{:02}", hours, minutes, seconds);
}

fn i_want_2_die(a: bool, b: bool, c: bool, d: bool) -> bool {
    let true_count = [a, b, c, d].iter().filter(|&&x| x).count();
    let _false_count = 4 - true_count;

    true_count == 2 || _false_count == 2
}

fn scan_bool() -> bool {
    let mut input = String::new();

    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");

    let bool_value: bool = match input.trim().to_lowercase().as_str() {
        "true" => true,
        "false" => false,
        _ => {
            println!("Invalid input. Please enter 'true' or 'false'.");
            std::process::exit(1);
        }
    };
    bool_value
}
fn enter_variables() {
    let a = scan_bool();
    let b = scan_bool();
    let c = scan_bool();
    let d = scan_bool();
    i_want_2_die(a, b, c, d);
}

//Пирожок в столовой стоит rubles рублей и  kopecks копеек. Определите, сколько рублей и копеек нужно заплатить за number_of_pies пирожков.
fn scan_uint() -> u32 {
    let mut input = String::new();
    std::io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");
    let number: u32 = input.trim().parse().expect("Failed to parse number");
    number
}
fn how_mach(rubles: u32, kopecks: u32, number_of_pies: u32) -> (u32, u32) {
    let total_kopecks = (rubles * 100 + kopecks) * number_of_pies;
    let calc_rubles = total_kopecks / 100;
    let calc_kopecks = total_kopecks % 100;
    (calc_rubles, calc_kopecks)
}
fn enter() {
    let rubles = scan_uint();
    let kopecks = scan_uint();
    let number_of_pies = scan_uint();

    let (p_r, p_k) = how_mach(rubles, kopecks, number_of_pies);
    println!("{} {}", p_r, p_k);
}
pub fn check(a: i32, b: i32, c: i32) -> String {
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
        "Существует".to_string()
    } else {
        "Не существует".to_string()
    }
}

pub fn cows(n: u32) -> () {
    if 11 <= n%100 && n%100<= 14 {
        println!("{} коров", n)
    } else if n%10==1 {
        println!("{} корова", n)
    } else if 2<=n%10 && n%10<=4 {
        println!("{} коровы", n)
    }else {
        println!("{} коров", n)
    }
}
