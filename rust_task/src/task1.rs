use std::io;
mod task1;

fn main() {
    let x: i32 = 1337;
    let y:i32;
    {
        y= 45;
        println!("x равен {}, а y равен {}", x, y);
    }
    println!("x равен {}, а y равен {}", x, y);
}
