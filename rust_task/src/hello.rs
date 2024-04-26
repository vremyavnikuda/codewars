fn main() {
    println!("Hello");
    
    let greeting = hello();
    println!("{}", greeting)
}

// Add your tests here.
fn hello() -> String {
    let hello = String::from("Hello");
    hello
}
