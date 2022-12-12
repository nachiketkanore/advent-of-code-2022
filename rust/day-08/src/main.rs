#![allow(unused)]
fn main() {}

const INF: u32 = 1000_000_000;

enum Direction {
    Left,
    Right,
    Up,
    Down,
}

fn dx_dy(direction: Direction) -> (i32, i32) {
    match direction {
        Direction::Up => (-1, 0),
        Direction::Down => (1, 0),
        Direction::Left => (0, -1),
        Direction::Right => (0, 1),
    }
}

struct Matrix {
    n: i32,
    m: i32,
    mat: Vec<Vec<char>>,
}

impl Matrix {
    fn lies_inside(&self, i: i32, j: i32) -> bool {
        return 0 <= i && i < self.n && 0 <= j && j < self.m;
    }

    fn get_score_in_direction_from(&self, i: usize, j: usize, direction: Direction) -> i32 {
        let (dx, dy) = dx_dy(direction);
        let mut max = -1;
        let (mut i, mut j) = (i as i32, j as i32);
        let cell_value = self.mat[i as usize][j as usize] as i32 - '0' as i32;
        let mut score = 0;
        i += dx;
        j += dy;
        while self.lies_inside(i, j) {
            let val = self.mat[i as usize][j as usize] as i32 - '0' as i32;
            if val >= cell_value {
                score += 1;
                break;
            }
            score += 1;
            i += dx;
            j += dy;
        }
        return score;
    }
    fn get_max_in_direction_from(&self, i: usize, j: usize, direction: Direction) -> i32 {
        let (dx, dy) = dx_dy(direction);
        let mut max = -1;
        let (mut i, mut j) = (i as i32, j as i32);
        i += dx;
        j += dy;
        while self.lies_inside(i, j) {
            let val = self.mat[i as usize][j as usize] as i32 - '0' as i32;
            if val > max {
                max = val;
            }
            i += dx;
            j += dy;
        }
        return max;
    }
}

fn solve_part1(input: &str) -> u32 {
    let mat: Vec<Vec<char>> = input
        .split('\n')
        .filter(|line| !line.is_empty())
        .map(|line| line.chars().collect::<Vec<char>>())
        .collect();

    let grid = Matrix {
        n: mat.len() as i32,
        m: mat[0].len() as i32,
        mat,
    };
    let mut answer = 0;
    for i in 0..grid.n as usize {
        for j in 0..grid.m as usize {
            let cell_value = grid.mat[i as usize][j as usize] as i32 - '0' as i32;
            let out = [
                grid.get_max_in_direction_from(i, j, Direction::Up),
                grid.get_max_in_direction_from(i, j, Direction::Down),
                grid.get_max_in_direction_from(i, j, Direction::Left),
                grid.get_max_in_direction_from(i, j, Direction::Right),
            ];
            answer += out
                .iter()
                .any(|max| max < &cell_value)
                .then_some(1)
                .or_else(|| Some(0))
                .unwrap();
        }
    }
    answer
}

fn solve_part2(input: &str) -> i32 {
    let mat: Vec<Vec<char>> = input
        .split('\n')
        .filter(|line| !line.is_empty())
        .map(|line| line.chars().collect::<Vec<char>>())
        .collect();

    let grid = Matrix {
        n: mat.len() as i32,
        m: mat[0].len() as i32,
        mat,
    };
    let mut answer = 0;
    for i in 0..grid.n as usize {
        for j in 0..grid.m as usize {
            let cell_value = grid.mat[i as usize][j as usize] as i32 - '0' as i32;
            let out = [
                grid.get_score_in_direction_from(i, j, Direction::Up),
                grid.get_score_in_direction_from(i, j, Direction::Down),
                grid.get_score_in_direction_from(i, j, Direction::Left),
                grid.get_score_in_direction_from(i, j, Direction::Right),
            ];
            let score = out.iter().fold(1, |result, val| result * val);
            answer = std::cmp::max(answer, score);
        }
    }
    answer
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn samples_part1() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part1(input), 21);
    }

    #[test]
    fn samples_part2() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part2(input), 8);
    }

    #[test]
    fn part1() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part1(input), 1715);
    }

    #[test]
    fn part2() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part2(input), 374400);
    }
}
