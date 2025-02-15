fn main() {
    let number: [i32; 5] = [1, 2, 3, 4, 5];
    println!("{:?}", number);

    let fruits: [&str; 3] = ["apple", "banana", "orange"];
    println!("{:?}", fruits);
    println!("{:}", fruits[1]);

    let human: (String, i32, bool) = ("Alice".to_string(), 32, true);

    println!("{} {} {}", human.0, human.1, human.2);
    let my_mix_tuple = ("Kratos", 23, true, [1, 2, 3, 4, 5, 6]);
    println!("My Mix Tuple is : {:?}", my_mix_tuple);

    let number_slice: &[i32] = &[1, 2, 3, 4, 5];
    println!("Numbers is slice : {:?}", number_slice);

    let animal_slice: &[&str] = &["Lion", "Tiger", "Elephant"];
    println!("Animal is slice:{:?}", animal_slice);

    let books_slice: &[&String] = &[&"Li".to_string(), &"Ti".to_string(), &"El".to_string()];
    println!("Books is slice:{:?}", books_slice);

    let mut stone_could: String = String::from("Hell,");
    println!("Stone could say:{}", stone_could);

    stone_could.push_str("Yeah!");

    println!("Stone could say:{}", stone_could);

    //
    println!("============= B- &str (String Slice) ==============");
    let string: String = String::from("Hello World");
    let slice: &str = &string[0..7];
    println!("Slice value:{}", slice);
}
