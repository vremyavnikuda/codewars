fn is_increasing(list: Vec<i32>) -> bool {
    if !list.is_empty() {
        for i in 0..list.len() - 1 {
            if list[i] >= list[i + 1] {
                return false;
            }
        }
        return true;
    }
    true
}

/// .? len 
fn text_len(_len:&str)-> i8{
    _len.len() as i8
}

#[allow(dead_code)]
fn main() {
    // Test cases
    let test1 = vec![1, 2, 3, 4, 5];
    let test2 = vec![5, 4, 3, 2, 1];
    let test3 = vec![1, 2, 2, 4, 5];
    let test4 = vec![];
    let test5 = vec![1];

    // Assertions
    assert_eq!(is_increasing(test1), true); // strictly increasing
    assert_eq!(is_increasing(test2), false); // strictly decreasing
    assert_eq!(is_increasing(test3), false); // not strictly increasing
    assert_eq!(is_increasing(test4), true); // empty list
    assert_eq!(is_increasing(test5), true); // single element

    println!("All tests passed!");
}