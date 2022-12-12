#![allow(unused)]
fn main() {}

fn solve_part1(input: &str) -> u32 {}

fn solve_part2(input: &str) -> u32 {}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn samples_part1() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part1(input), ());
    }

    #[test]
    fn samples_part2() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part2(input), ());
    }

    #[test]
    fn part1() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part1(input), ());
    }

    #[test]
    fn part2() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part2(input), ());
    }
}
