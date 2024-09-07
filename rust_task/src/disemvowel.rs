#[allow(unused)]
//Удаляем все гласные буквы
fn disemvowel(s: &str) -> String {
    let word = "aeiouAEIOU";
    let mut result = String::new();

    for c in s.chars() {
        if !word.contains(c) {
            result.push(c);
        }
    }
    result
}
#[allow(unused)]
fn main() {
    println!("{}", disemvowel("hello"));
    println!("{}", double_char("hello"))
}
//Дублируем все буквы в словах
fn double_char(s: &str) -> String {
    let mut _result = String::new();

    for word in s.chars() {
        if s.contains(word) {
            _result.push(word);
            _result.push(word);
        }
    }
    _result
}
