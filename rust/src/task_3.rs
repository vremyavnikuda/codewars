fn main() {
    //int16();
    // if_construction();
    // match_construction();
    // loop_function();
    // for_condition();
    // ref_cycle();
    // func_ref(10);
    // func_for_func(10, 10);
    // println!("{}", func_for_func(4, 4));
    // an_func(10);
    sum_an_func();
}

#[warn(dead_code)]
fn int16() {
    let int16_number: i16 = 10;
    println!("{}", int16_number);

    let int32: i32 = int16_number as i32;
    println!("{}", int32);
}

fn if_construction() {
    let number = 12;

    if number > 10 {
        println!("{} is greater than 10", number);
    } else {
        println!("{} is less than 10", number);
    }
}

fn match_construction() {
    let number: i8 = 2;
    match number {
        1 => println!("One"),
        2 => println!("Two"),
        3 => println!("Three"),
        4 => println!("Four"),
        5 => println!("Five"),
        _ => println!("Unknown number"),
    }
}

fn loop_function() {
    let mut number = 10;

    let result = loop {
        println!("{}", number);

        number = number - 1;
        if number == 0 {
            break;
        }
    };
    println!("{:?}", result);
}

fn for_condition() {
    for num in 1..10 {
        println!("{}", num);
    }
    println!("end program");
}
fn ref_cycle() {
    let mut count = 0;
    'outer: loop {
        println!("count = {count}");
        let mut remaining = 10;
        loop {
            println!("remaining = {remaining}");
            if remaining == 9 {
                break;
            }
            if count == 2 {
                break 'outer;
            }
            remaining -= 1;
        }
        count += 1;
    }
    println!("Final count = {count}");
}

fn func_ref(number: i32) {
    let result: i32 = number + number;
    println!("{}", result);
}

/// Multiplies two 8-bit integers after converting them to 32-bit integers.
///
/// # Arguments
///
/// * `a` - An 8-bit integer to be multiplied.
/// * `b` - Another 8-bit integer to be multiplied.
///
/// # Returns
///
/// * A 32-bit integer representing the product of the two input integers after conversion.
///
/// # Example
///
/// ```
/// let result = func_for_func(4, 4);
/// assert_eq!(result, 16);
/// ```
fn func_for_func(a: i8, b: i8) -> i32 {
    fn type_variable(a: i8, b: i8) -> (i32, i32) {
        let par_1: i32 = a as i32;
        let par_2: i32 = b as i32;
        (par_1, par_2)
    }
    let (par_1, par_2) = type_variable(a, b);
    par_1 * par_2
}

/// Function which takes a number and returns its square.
///
/// Additionally, it prints the result of squaring the number.
///
/// # Examples
/// ```
/// let result = an_func(10);
/// println!("{}",result);
/// ```
fn an_func(n: i32) -> i32 {
    let func = |n: i32| {
        let result_func = n * n;
        println!("{}", result_func);
    };

    func(n);
    n
}

/// Returns the sum of two integers using a closure.
///
/// This function demonstrates the use of a closure to compute
/// the sum of two integers, and prints the result to the console.
///
/// # Example
///
/// ```
/// sum_an_func(); // Prints "20" to the console.
/// ```

fn sum_an_func() {
    let sum = |a: i32, b: i32| -> i32 { a + b };
    println!("{}", sum(10, 10));
}
