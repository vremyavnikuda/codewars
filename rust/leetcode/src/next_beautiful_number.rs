impl Solution {
    pub fn next_beautiful_number(n: i32) -> i32 {
        let mut candidate = n + 1;
        loop {
            let mut digit_frequency = [0; 10];
            let mut temp = candidate;
            while temp > 0 {
                let digit = temp % 10;
                digit_frequency[digit as usize] += 1;
                temp /= 10;
            }
            let mut is_beautiful = true;
            temp = candidate;
            while temp > 0 {
                let digit = temp % 10;
                if digit != digit_frequency[digit as usize] {
                    is_beautiful = false;
                    break;
                }
                temp /= 10;
            }
            if is_beautiful {
                return candidate;
            }
            candidate += 1;
        }
    }
}
