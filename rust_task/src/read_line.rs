//Поиск максимального значения массива 
//Через джeнерики
fn largest<T: PartialOrd>(list: &[T]) -> &T {
    let mut largest= &list[0];

    for item in list.iter(){
        if item>largest{
            largest=item;
        }
    }
    largest
}
//Дни недели в массиве данных
fn days<T:PartialOrd+ std::fmt::Display>(list: &[T]) -> &T {
    let mut day=&list[0];
    for item in list.iter(){
        println!("{}",item)
    }
    day
}

fn main(){
    let number = vec![34,50,423,234];
    let day=vec!["Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"];
    let resultNumber= largest(&number);
    let resultDay= days(&day);

    println!("The largest number is {}",resultNumber);
    println!("The largest day is {}",resultDay);
}