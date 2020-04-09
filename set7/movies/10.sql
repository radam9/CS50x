SELECT DISTINCT name FROM people
JOIN directors ON person_id = people.id
JOIN movies ON directors.movie_id = movies.id
JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE rating >= 9.0;
