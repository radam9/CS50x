SELECT AVG(rating) FROM ratings WHERE (SELECT year FROM movies WHERE movie_id = id) = 2012;
