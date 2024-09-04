fn last_symbol(txt: &str) -> String {
    if let Some(last_char) = txt.chars().last() {
        println!("{}", last_char);
        last_char.to_string()
    } else {
        println!("empty string");
        "empty string".to_string()
    }
}

#[allow(unused)]
fn main() {
    println!("{}",two_word("abc", "ade"))
}

fn two_word(word1:&str,word2:&str)->bool{
    match (word1.chars().next(),word2.chars().next()) {
        (Some(c1),Some(c2))=> c1==c2,
        _=>false,
    }
}