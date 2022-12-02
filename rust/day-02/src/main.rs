fn main() {}

fn choice_score(b: &str) -> u32 {
    match b {
        "A" => 1,
        "B" => 2,
        "C" => 3,
        _ => panic!(),
    }
}

fn get_score(a: &str, b: &str) -> u32 {
    let mut ans = choice_score(b);
    let winners = vec![vec!["A", "C"], vec!["B", "A"], vec!["C", "B"]];
    if winners.contains(&vec![b, a]) {
        ans += 6;
    }
    if a == b {
        ans += 3;
    }
    return ans;
}

fn solve_part1(input: &String) -> u32 {
    input
        .split('\n')
        .map(|line| line.split(' ').collect())
        .filter(|line: &Vec<&str>| line.len() == 2)
        .fold(0, |res, line| {
            let (a, mut b) = (line[0], line[1]);
            b = match b {
                "X" => "A",
                "Y" => "B",
                "Z" => "C",
                _ => panic!(),
            };
            res + get_score(a, b)
        })
}

fn get_loser_against(s: &str) -> &str {
    match s {
        "A" => "C",
        "B" => "A",
        "C" => "B",
        _ => panic!(),
    }
}

fn get_winner_against(s: &str) -> &str {
    match s {
        "A" => "B",
        "B" => "C",
        "C" => "A",
        _ => panic!(),
    }
}

fn solve_part2(input: &String) -> u32 {
    input
        .split('\n')
        .map(|line| line.split(' ').collect())
        .filter(|line: &Vec<&str>| line.len() == 2)
        .fold(0, |res, line| {
            let (a, mut b) = (line[0], line[1]);
            b = match b {
                "X" => get_loser_against(a),
                "Y" => a,
                "Z" => get_winner_against(a),
                _ => panic!(),
            };
            res + get_score(a, b)
        })
}

#[cfg(test)]
pub mod tests {
    use super::*;

    #[test]
    fn samples_part1() {
        let input = std::fs::read_to_string("./data/sample.txt").unwrap();
        assert_eq!(solve_part1(&input), 15);
    }

    #[test]
    fn samples_part2() {
        let input = std::fs::read_to_string("./data/sample.txt").unwrap();
        assert_eq!(solve_part2(&input), 12);
    }

    #[test]
    fn part1() {
        let input = std::fs::read_to_string("./data/input.txt").unwrap();
        assert_eq!(solve_part1(&input), 10718);
    }

    #[test]
    fn part2() {
        let input = std::fs::read_to_string("./data/input.txt").unwrap();
        assert_eq!(solve_part2(&input), 14652);
    }
}
