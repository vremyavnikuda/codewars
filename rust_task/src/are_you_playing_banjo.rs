fn are_you_playing_banjo(name: &str) -> String {
    if name.to_lowercase().starts_with("r") {
        return format!("{} plays banjo", name);
    }
    format!("{} does not play banjo", name)
}

// See https://doc.rust-lang.org/stable/rust-by-example/testing/unit_testing.html
#[cfg(test)]
mod tests {
    use super::are_you_playing_banjo;

    #[test]
    fn test_are_you_playing_banjo() {
        assert_eq!(are_you_playing_banjo("Martin"), "Martin does not play banjo");
        assert_eq!(are_you_playing_banjo("Rikke"), "Rikke plays banjo");
        assert_eq!(are_you_playing_banjo("bravo"), "bravo does not play banjo");
        assert_eq!(are_you_playing_banjo("rolf"), "rolf plays banjo");
    }
}
