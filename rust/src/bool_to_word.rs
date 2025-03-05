fn bool_to_word(value:bool)-> &'static str {
    if value {
        "Yes"
    }else {
        "No"
    }
}
// https://doc.rust-lang.org/stable/rust-by-example/testing/unit_testing.html
#[cfg(test)]
mod tests {
    use super::bool_to_word;

    #[test]
    fn example_tests() {
        assert_eq!(bool_to_word(true), "Yes");
        assert_eq!(bool_to_word(false), "No");
    }
}

use nom::error::ErrorKind;

fn handle_parsing_errors(input: &str) {
    match parse_abcdef(input) {
        Ok((remaining, result)) => {
            println!("Успешный парсинг!");
            println!("Результат: {:?}", result);
            println!("Оставшаяся строка: {}", remaining);
        },
        Err(nom::Err::Error(e)) => {
            println!("Ошибка парсинга: {:?}", e);
        },
        Err(e) => println!("Другая ошибка: {:?}", e),
    }
}
let program = vec![
    Statement::Assign(
        Identifier("x".to_string()),
        Expression::Add(
            Box::new(Expression::Number(Number(5))),
            Box::new(Expression::Number(Number(3)))
        )
    ),
    Statement::If(
        Box::new(
            Expression::Comp(
                Box::new(Expression::Identifier(Identifier("x".to_string()))),
                Box::new(Expression::Number(Number(8)))
            )
        ),
        Box::new(
            Statement::Print(
                Expression::Mul(
                    Box::new(Expression::Identifier(Identifier("x".to_string()))),
                    Box::new(Expression::Number(Number(2)))
                )
            )
        ),
        Some(Box::new(Statement::Print(Expression::Number(Number(0)))))
    )
];
for stmt in program {
    compile_program(stmt);
}
