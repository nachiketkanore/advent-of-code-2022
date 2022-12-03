#![allow(unused)]
fn main() {}

fn get_char_score(ch: char) -> u32 {
    match ch {
        'a'..='z' => ch as u32 - 'a' as u32 + 1,
        'A'..='Z' => ch as u32 - 'A' as u32 + 1 + 26,
        _ => panic!("invalid char"),
    }
}

fn solve_part1(input: &str) -> u32 {
    let mut chars = vec![];
    ('a'..='z').for_each(|ch| chars.push(ch));
    ('A'..='Z').for_each(|ch| chars.push(ch));
    input
        .lines()
        .map(|line| line.split_at(line.len() / 2))
        .fold(0, |res, (a, b)| {
            res + chars
                .iter()
                .filter(|&ch| a.contains(*ch) && b.contains(*ch))
                .fold(0, |add, ch| add + get_char_score(*ch))
        })
}

fn solve_part2(input: &str) -> u32 {
    let mut chars = vec![];
    ('a'..='z').for_each(|ch| chars.push(ch));
    ('A'..='Z').for_each(|ch| chars.push(ch));
    input
        .lines()
        .collect::<Vec<&str>>()
        .chunks(3)
        .map(|chunk| {
            (
                chunk.get(0).unwrap(),
                chunk.get(1).unwrap(),
                chunk.get(2).unwrap(),
            )
        })
        .fold(0, |res, (&a, &b, &c)| {
            res + chars
                .iter()
                .filter(|&ch| a.contains(*ch) && b.contains(*ch) && c.contains(*ch))
                .fold(0, |add, ch| add + get_char_score(*ch))
        })
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn samples_part1() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part1(input), 157);
    }

    #[test]
    fn samples_part2() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part2(input), 70);
    }

    #[test]
    fn part1() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part1(input), 8394);
    }

    #[test]
    fn part2() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part2(input), 2413);
    }
}
