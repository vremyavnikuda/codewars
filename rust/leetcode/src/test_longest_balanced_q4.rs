mod longest_balanced_q4;

fn main() {
    // Test cases
    let test1 = vec![0, 1, 3, 2];
    let result1 = longest_balanced_q4::Solution::longest_balanced(test1);
    println!("Test 1: {} (expected: 2)", result1);

    let test2 = vec![0, 1, 1, 0, 2];
    let result2 = longest_balanced_q4::Solution::longest_balanced(test2);
    println!("Test 2: {} (expected: 4)", result2);

    let test3 = vec![1, 1, 1];
    let result3 = longest_balanced_q4::Solution::longest_balanced(test3);
    println!("Test 3: {} (expected: 0)", result3);

    let test4 = vec![0, 0, 0];
    let result4 = longest_balanced_q4::Solution::longest_balanced(test4);
    println!("Test 4: {} (expected: 0)", result4);

    let test5 = vec![0, 1, 0, 1];
    let result5 = longest_balanced_q4::Solution::longest_balanced(test5);
    println!("Test 5: {} (expected: 4)", result5);

    let test6 = vec![1, 0, 1, 0, 1, 0];
    let result6 = longest_balanced_q4::Solution::longest_balanced(test6);
    println!("Test 6: {} (expected: 6)", result6);

    let test7 = vec![];
    let result7 = longest_balanced_q4::Solution::longest_balanced(test7);
    println!("Test 7: {} (expected: 0)", result7);

    let test8 = vec![2];
    let result8 = longest_balanced_q4::Solution::longest_balanced(test8);
    println!("Test 8: {} (expected: 0)", result8);

    let test9 = vec![1];
    let result9 = longest_balanced_q4::Solution::longest_balanced(test9);
    println!("Test 9: {} (expected: 0)", result9);
}