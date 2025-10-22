impl Solution {
    pub fn num_water_bottles(num_bottles: i32, num_exchange: i32) -> i32 {
        let mut total_drunk = num_bottles;
        let mut bottles = num_bottles;
        while bottles >= num_exchange {
            bottles -= (num_exchange - 1);
            total_drunk += 1;
        }
        total_drunk
    }
}