use std::io;
fn main() {
    println!("{}", add(1, 2));
    sum_number();
    sum_number();
}

fn add(left: usize, right: usize) -> usize {
    left + right
}

/// This function creates a program consisting of assignment and conditional statements.
/// It assigns the sum of two numbers to a variable `x`, checks if `x` is equal to 8,
/// and then prints either the product of `x` and 2 or 0, depending on the result.
/// The program is then compiled and executed.

fn sum_number() {
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
    for stmt in program {
        execute_program(stmt);
    }
}
