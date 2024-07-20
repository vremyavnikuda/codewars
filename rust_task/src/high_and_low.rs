fn high_and_low(numbers: &str) -> String {
    let mut nums : Vec <i32> = numbers.split_whitespace().map(|nums|nums.parse().unwrap()).collect();

    nums.sort();

    let max =nums.last().unwrap();
    let min =nums.first().unwrap();

    format!("{} {}",max,min)
}
#[test]
fn example_test_1() {
    assert_eq!("42 -9", high_and_low("8 3 -5 42 -1 0 0 -9 4 7 4 -4"));
}

#[test]
fn example_test_2() {
    assert_eq!("3 1", high_and_low("1 2 3"));
}
