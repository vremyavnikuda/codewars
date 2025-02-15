pub fn type_data() {
    let x = 128;
    let y = 128;
    let z = 128;
    println!("x = {}, y = {}, z = {}", x, y, z);
}


fn main() {
    type_data();
    println!("result complete");
    let numbers = [10, 20, 30, 40, 50];
    let result = largest(&numbers);
    println!("largest = {}", result);
    
    let chars=vec!{'y','a','b','n'};
    let result = largest(&chars);
    println!("largest = {}", result);
}

pub fn largest<T:PartialOrd>(list:&[T])-> &T{
    let mut lagest = &list[0];
    for item in list.iter(){
        if item>lagest{
            lagest=item;
        }
    }
    lagest
}