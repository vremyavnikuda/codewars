#![allow(unused)]
fn number_is_positive(num:i32)->String{
    if num.is_positive(){
        println!("Number is positive");
        return "positive".to_string();
    }else{
        println!("Number is not positive");
        return "negative".to_string();
    }
}

fn text_len(_len:&str)->i32{
    return _len.len();
}

fn main(){
    number_is_positive(123);
    text_len("abcde");
}