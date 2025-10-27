impl Solution {
    pub fn number_of_beams(bank: Vec<String>) -> i32 {
        let mut total_beams = 0;
        let mut previous_device_count = 0;
        for row in &bank {
            let current_device_count = row.chars().filter(|&c| c == '1').count() as i32;
            if current_device_count > 0 {
                total_beams += previous_device_count * current_device_count;
                previous_device_count = current_device_count;
            }
        }
        total_beams
    }
}
