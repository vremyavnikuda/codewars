pub mod task;
pub mod are_you_playing_banjo;
mod task2;

fn main() {
    let mut input_string= String::new();
    
    std::io::stdin().read_line(&mut input_string).expect("Failed to read line");
    let number : i32= input_string.trim().parse().expect("Not a number");
    
    let result = (number*2)+100;
    println!("{}",result);
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
