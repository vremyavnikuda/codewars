pub mod task1;

pub fn task1(){
    let number_of_stars:u64;

    number_of_stars = 400_000_000;
    println!("Около {} звёзд в галактике Млечный Путь, относящейся к типу спиральных галактик с перемычкой!", number_of_stars);
}


fn main(){
    task1::task1();
    task1::number1();
}
pub fn number1(){
    let x:i32=-42;
    let y:u64=100;
    println!("{}",x);
    println!("{}",y);
}
