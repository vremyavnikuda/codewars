fn main() {
    let number = Number(12);
    let text = Text(String::from("value"));
    
    print_all(&number);
    print_all(&text);
}

trait Printable {
    fn print(&self);
}
struct Number(i32);
impl Printable for Number {
    fn print(&self) {
        println!("number: {}", self.0);
    }
}
struct Text(String);
impl Printable for Text {
    fn print(&self) {
        println!("text: {}", self.0);
    }
}
fn print_all<T:Printable>(items: &T){
    items.print();
}

