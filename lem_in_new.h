#ifndef LEM_IN

# define LEM_IN

struct s_room
{
	connections	*neighbors;
	int			level;
};

typedef struct s_room room;

struct s_connections
{
	int		count;
	room	*rooms;
};

typedef struct s_connections connections;

struct s_ant
{
	room	*current_room;
	room	*target_room;
	int		id;
};

typedef struct s_ant ant;

struct s_farm
{
	room	*start_room;
	room	*target_room;
	ant		*ants;
	// ant		**ants;
	int		count_ants;
};

// TODO Write initialize code and alloc functions

# endif