pub fn cockroach_speed (s:f64)->i64{
    match s { 
        s if s!=0.0 => (s * 100000.0/3600.0).floor() as i64,
        _ => 0,
    }
}

#[cfg(test)]
mod sample_tests {
    use super::cockroach_speed;

    #[test]
    fn basic_tests() {
        test(1.08, 30);
        test(1.09, 30);
        test(0.0, 0);
    }

    fn test(speed: f64, expected: i64) {
        let actual = cockroach_speed(speed);
        assert_eq!(actual, expected, "\nYour result (left) did not match the expected result (right) for the speed {speed}");
    }
}