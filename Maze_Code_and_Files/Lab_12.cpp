#include "library.h";
image * robot_icon = image_from_file("robot2.bmp");
image * treasure_icon = image_from_file("treasure.bmp");
image * player_icon = image_from_file("penguin.bmp");
char maze[100][100];
int has_moved[100][100][2];
int initial_p_x, initial_p_y, player_x, player_y, enemy_x, enemy_y, prize_x, prize_y, num_rows, num_cols, sq = 25;
bool p_e_move[2][5] = { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } };
void read_store_maze(string file){
	int i = 0;
	string row;
	ifstream fin(file);
	if (fin.fail()){
		cout << "Can't Open File!";
	}
	else{
		while (!fin.eof()){
			getline(fin, row);
			for (int j = 0; j < row.length(); j++){
				maze[i][j] = row[j];
			}
			num_cols = row.length();
			i++;
		}
		num_rows = i;
		fin.close();
	}
	for (int i = 0; i < num_rows; i++){
		for (int j = 0; j < num_cols; j++){
			has_moved[i][j][0] = -1;
			has_moved[i][j][1] = -1;
		}
	}
	for (int i = 0; i < num_rows; i++){
		for (int j = 0; j < num_cols; j++){
			if (maze[i][j] == '#'){
				has_moved[i][j][0] = -2;
				has_moved[i][j][1] = -2;
			}
		}
	}
}
void spawn_player(){
	int x, y, flag = 0;
	while (flag != -1){
		x = random_in_range(0, num_cols);
		y = random_in_range(0, num_rows);
		if (maze[y][x] == ' '){
			maze[y][x] = '+';
			flag = -1;
		}
	}
}
void spawn_enemy(){
	int x, y, flag = 0;
	while (flag != -1){
		x = random_in_range(0, num_cols);
		y = random_in_range(0, num_rows);
		if (maze[y][x] == ' '){
			maze[y][x] = 'E';
			flag = -1;
		}
	}
}
void spawn_treasure(){
	int x, y, flag = 0;
	while (flag != -1){
		x = random_in_range(0, num_cols);
		y = random_in_range(0, num_rows);
		if (maze[y][x] == ' '){
			maze[y][x] = '$';
			flag = -1;
		}
	}
}
void find_player_enemy_prize(){
	for (int i = 0; i < num_rows; i++){
		for (int j = 0; j < num_cols; j++){
			if (maze[i][j] == '+'){
				initial_p_y = i;
				initial_p_x = j;
				player_y = i;
				player_x = j;
			}
			if (maze[i][j] == 'E'){
				enemy_y = i;
				enemy_x = j;
			}
			else if (maze[i][j] == '$'){
				prize_y = i;
				prize_x = j;
			}
		}
	}
	cout << "Greeen Player:" << "(" << player_x << "," << player_y << ")" << endl;
	cout << "Blue Enemy:" << "(" << enemy_x << "," << enemy_y << ")" << endl;
	cout << "Red Prize:" << "(" << prize_x << "," << prize_y << ")" << endl;
}
void one_square(int x, int y, char sym){
	set_pen_color(color::black);
	fill_rectangle(x, y, sq, sq);	
	if (sym == '#'){
		set_pen_color(color::dark_grey);
		fill_rectangle(x, y, sq - sq / 10, sq - sq / 10);
	}
	else if (sym == ' '){
		set_pen_color(color::white);
		fill_rectangle(x, y, sq - sq / 10, sq - sq / 10);
	}
	else if (sym == 'Y'){
		set_pen_color(color::yellow);
		fill_rectangle(x, y, sq - sq / 10, sq - sq / 10);
	}
	else if (sym == '+'){
		draw_image(player_icon, x, y);
	}
	else if (sym == 'E'){
		draw_image(robot_icon, x, y);
	}
	else if (sym == '$'){
		draw_image(treasure_icon, x, y);
	}
}
void draw_maze(){
	for (int i = 0; i < num_rows; i++){
		for (int j = 0; j < num_cols; j++){
			one_square(j*sq, i*sq, maze[i][j]);
		}
	}
}
void print_maze(){
	for (int i = 0; i < num_rows; i++){
		for (int j = 0; j < num_cols; j++){
			cout << maze[i][j];
		}
		cout << endl;
	}
}
bool isTreasure(int x, int y, int direction){
	if (direction == 0){
		if (maze[y - 1][x] == '$'){
			return true;
		}
	}
	else if (direction == 1){
		if (maze[y][x + 1] == '$'){
			return true;
		}
	}
	else if (direction == 2){
		if (maze[y + 1][x] == '$'){
			return true;
		}
	}
	else if (direction == 3){
		if (maze[y][x - 1] == '$'){
			return true;
		}
	}
	return false;
}
bool notBeenThere(int x, int y, int p_e, int direction){
	if (direction == 0){
		if (has_moved[y - 1][x][p_e] ==-1){
			return true;
		}
	}
	else if (direction == 1){
		if (has_moved[y][x + 1][p_e] ==-1){
			return true;
		}
	}
	else if (direction == 2){
		if (has_moved[y + 1][x][p_e] ==-1){
			return true;
		}
	}
	else if (direction == 3){
		if (has_moved[y][x - 1][p_e] ==-1){
			return true;
		}
	}
	return false;
}
void move_p_e(int direction, int p_e, char sym){
	if (direction == 0){
		if (p_e == 0){
			maze[player_y - 1][player_x] = '+';
			maze[player_y][player_x] = sym;
			player_y--;
			draw_maze();
		}
		else if (p_e == 1){
			if (maze[enemy_y - 1][enemy_x] == 'Y'){
				maze[enemy_y][enemy_x] = 'Y';
				
			}
			else{
				maze[enemy_y][enemy_x] = sym;
			}
			maze[enemy_y - 1][enemy_x] = 'E';
			enemy_y--;
			draw_maze();
		}
	}
	else if (direction == 1){
		if (p_e == 0){
			maze[player_y][player_x + 1] = '+';
			maze[player_y][player_x] = sym;
			player_x++;
			draw_maze();
		}
		else if (p_e == 1){
			if (maze[enemy_y][enemy_x + 1] == 'Y'){
				maze[enemy_y][enemy_x] = 'Y';
				
			}
			else{
				maze[enemy_y][enemy_x] = sym;
			}
			maze[enemy_y][enemy_x + 1] = 'E';
			enemy_x++;
			draw_maze();
		}
	}
	else if (direction == 2){
		if (p_e == 0){
			maze[player_y + 1][player_x] = '+';
			maze[player_y][player_x] = sym;
			player_y++;
			draw_maze();
		}
		else if (p_e == 1){
			if (maze[enemy_y + 1][enemy_x] == 'Y'){
				maze[enemy_y][enemy_x] = 'Y';
				
			}
			else{
				maze[enemy_y][enemy_x] = sym;
			}
			maze[enemy_y + 1][enemy_x] = 'E';
			enemy_y++;
			draw_maze();
		}
	}
	else if (direction == 3){
		if (p_e == 0){
			maze[player_y][player_x - 1] = '+';
			maze[player_y][player_x] = sym;
			player_x--;
			draw_maze();
		}
		else if (p_e == 1){
			if (maze[enemy_y][enemy_x - 1] == 'Y'){
				maze[enemy_y][enemy_x] = 'Y';
				
			}
			else{
				maze[enemy_y][enemy_x] = sym;
			}
			maze[enemy_y][enemy_x - 1] = 'E';
			enemy_x--;
			draw_maze();
		}
	}
}
void auto_set(int x, int y, int p_e){
	if (maze[y - 1][x] == '#'){
		p_e_move[p_e][0] = false;
	}
	else{
		p_e_move[p_e][0] = true;
	}
	if (maze[y][x + 1] == '#'){
		p_e_move[p_e][1] = false;
	}
	else{
		p_e_move[p_e][1] = true;
	}
	if (maze[y + 1][x] == '#'){
		p_e_move[p_e][2] = false;
	}
	else{
		p_e_move[p_e][2] = true;
	}
	if (maze[y][x - 1] == '#'){
		p_e_move[p_e][3] = false;
	}
	else{
		p_e_move[p_e][3] = true;
	}
}
bool isGameOver(){
	bool yes_enemy = false;
	bool yes_player = false;
	for (int i = 0; i < num_rows; i++){
		for (int j = 0; j < num_cols; j++){
			if (maze[i][j] == '+'){
				yes_player = true;
			}
			if (maze[i][j] == 'E'){
				yes_enemy = true;
			}
		}
	}
	if (yes_enemy&&yes_player){
		return false;
	}else{
		return true;
	}
}
void enemy_auto(int mode){
	auto_set(enemy_x, enemy_y, 1);
	if (mode == 0){
		while (true){
			int rand_sq_e = random_in_range(0, 3);
			if (isTreasure(enemy_x, enemy_y, rand_sq_e)){
				p_e_move[1][rand_sq_e] = false;
			}
			if (p_e_move[1][rand_sq_e]){
				move_p_e(rand_sq_e, 1, ' ');
				if (rand_sq_e <= 1){
					has_moved[enemy_y][enemy_x][1] = rand_sq_e + 2;
				}
				else{
					has_moved[enemy_y][enemy_x][1] = (rand_sq_e - 2);
				}
				break;
			}
		}
	}else{
		while (true){
			if (isTreasure(enemy_x, enemy_y, 0) || isTreasure(enemy_x, enemy_y, 1) || isTreasure(enemy_x, enemy_y, 2) || isTreasure(enemy_x, enemy_y, 3)){
				break;
			}
			int rand_sq_e = random_in_range(0, 3);
			if (isTreasure(enemy_x, enemy_y, rand_sq_e)){
				p_e_move[1][rand_sq_e] = false;
			}
			if (p_e_move[1][rand_sq_e] && notBeenThere(enemy_x, enemy_y, 1, rand_sq_e)){
				move_p_e(rand_sq_e, 1, ' ');
				if (rand_sq_e <= 1){
					has_moved[enemy_y][enemy_x][1] = rand_sq_e + 2;
				}else{
					has_moved[enemy_y][enemy_x][1] = (rand_sq_e - 2);
				}
				break;
			}else{
				if (!notBeenThere(enemy_x, enemy_y, 1, rand_sq_e)){
					p_e_move[1][rand_sq_e] = false;
				}
				if (!p_e_move[1][0] && !p_e_move[1][1] && !p_e_move[1][2] && !p_e_move[1][3]){
					move_p_e(has_moved[enemy_y][enemy_x][1], 1, ' ');
					break;
				}
			}
		}
	}
}
bool unsolvable(){
	if (has_moved[player_y - 1][player_x][0] == -1 ||
		has_moved[player_y + 1][player_x][0] == -1 ||
		has_moved[player_y][player_x + 1][0] == -1 ||
		has_moved[player_y][player_x - 1][0] == -1 ||
		has_moved[player_y - 1][player_x + 1][0] == -1 ||
		has_moved[player_y + 1][player_x + 1][0] == -1 ||
		has_moved[player_y + 1][player_x - 1][0] == -1 ||
		has_moved[player_y - 1][player_x - 1][0] == -1){
		return false;
	}
	if (has_moved[player_y - 1][player_x][0] != -2&&
		(has_moved[player_y-2][player_x][0]==-1||has_moved[player_y-2][player_x+1][0]==-1||has_moved[player_y-2][player_x-1][0]==-1)){
		return false;
	}
	if (has_moved[player_y][player_x+1][0] != -2 &&
		(has_moved[player_y][player_x+2][0] == -1 || has_moved[player_y - 1][player_x+2][0] == -1 || has_moved[player_y+1][player_x +2][0] == -1)){
		return false;
	}
	if (has_moved[player_y + 1][player_x][0] != -2 &&
		(has_moved[player_y + 2][player_x][0] == -1 || has_moved[player_y + 2][player_x + 1][0] == -1 || has_moved[player_y + 2][player_x - 1][0] == -1)){
		return false;
	}
	if (has_moved[player_y][player_x - 1][0] != -2 &&
		(has_moved[player_y][player_x - 2][0] == -1 || has_moved[player_y - 1][player_x - 2][0] == -1 || has_moved[player_y + 1][player_x - 2][0] == -1)){
		return false;
	}
	return true;
}
char new_semi_i_mode(int mode){
	char c = '0';
	while (c != 'm'){
		c = wait_for_key_typed(0.1);
		if (isGameOver()){
			break;
		}
		if (c == 'x'){
			return c;
		}
		if (p_e_move[0][4]){
			break;
		}
		if (player_x == initial_p_x&&player_y == initial_p_y){
			if (unsolvable()){
				break;
			}
		}
		if (c != 'm'){
			auto_set(player_x, player_y, 0);
			auto_set(enemy_x, enemy_y, 1);
			while (true){
				int rand_sq_p = random_in_range(0, 3);
				if (notBeenThere(player_x, player_y, 0, rand_sq_p) && p_e_move[0][rand_sq_p]){
					for (int i = 0; i < 4; i++){
						if (isTreasure(player_x, player_y, i)){
							rand_sq_p = i;
						}
					}
					if (isTreasure(player_x, player_y, rand_sq_p)){
						p_e_move[0][4] = true;
						move_p_e(rand_sq_p, 0, 'Y');
						cout << "Treasure was found! You win!" << endl;
					}
					else{
						move_p_e(rand_sq_p, 0, 'Y');
						if (rand_sq_p <= 1){
							has_moved[player_y][player_x][0] = rand_sq_p + 2;
						}
						else{
							has_moved[player_y][player_x][0] = (rand_sq_p - 2);
						}
						enemy_auto(mode);
					}
					break;
				}
				else{
					if (!notBeenThere(player_x, player_y, 0, rand_sq_p)){
						p_e_move[0][rand_sq_p] = false;
					}
					if (!p_e_move[0][0] && !p_e_move[0][1] && !p_e_move[0][2] && !p_e_move[0][3]){
						move_p_e(has_moved[player_y][player_x][0], 0, ' ');
						enemy_auto(mode);
						break;
					}
				}
			}
		}
	}
}
void gameplay(int mode){
	if (!unsolvable()){
		while (true){
			char c = wait_for_key_typed();
			if (p_e_move[0][4]){
				break;
			}
			if (c == 'w'){
				if (maze[player_y - 1][player_x] == '$'){
					move_p_e(0, 0, 'Y');
					enemy_auto(mode);
					cout << "You got the treasure! You win!" << endl;
					break;
				}
				if (maze[player_y - 1][player_x] != '#'){
					if (has_moved[player_y - 1][player_x][0] == -1){
						move_p_e(0, 0, 'Y');
						has_moved[player_y][player_x][0] = 2;
						enemy_auto(mode);
					}
					else{
						move_p_e(0, 0, ' ');
						has_moved[player_y][player_x][0] = 2;
						enemy_auto(mode);
					}
				}
				else{
					cout << "You've hit a wall!" << endl;
				}
			}
			else if (c == 'd'){
				if (maze[player_y][player_x + 1] == '$'){
					move_p_e(1, 0, 'Y');
					enemy_auto(mode);
					cout << "You got the treasure! You win!" << endl;
					break;
				}
				if (maze[player_y][player_x + 1] != '#'){
					if (has_moved[player_y][player_x + 1][0] == -1){
						move_p_e(1, 0, 'Y');
						has_moved[player_y][player_x][0] = 3;
						enemy_auto(mode);
					}
					else{
						move_p_e(1, 0, ' ');
						has_moved[player_y][player_x][0] = 3;
						enemy_auto(mode);
					}
				}
				else{
					cout << "You've hit a wall!" << endl;
				}
			}
			else if (c == 's'){
				if (maze[player_y + 1][player_x] == '$'){
					move_p_e(2, 0, 'Y');
					enemy_auto(mode);
					cout << "You got the treasure! You win!" << endl;
					break;
				}
				if (maze[player_y + 1][player_x] != '#'){
					if (has_moved[player_y + 1][player_x][0] == -1){
						move_p_e(2, 0, 'Y');
						has_moved[player_y][player_x][0] = 0;
						enemy_auto(mode);
					}
					else{
						move_p_e(2, 0, ' ');
						has_moved[player_y][player_x][0] = 0;
						enemy_auto(mode);
					}
				}
				else{
					cout << "You've hit a wall!" << endl;
				}
			}
			else if (c == 'a'){
				if (maze[player_y][player_x - 1] == '$'){
					move_p_e(3, 0, 'Y');
					enemy_auto(mode);
					cout << "You got the treasure! You win!" << endl;
					break;
				}
				if (maze[player_y][player_x - 1] != '#'){
					if (has_moved[player_y][player_x - 1][0] == -1){
						move_p_e(3, 0, 'Y');
						has_moved[player_y][player_x][0] = 1;
						enemy_auto(mode);
					}
					else{
						move_p_e(3, 0, ' ');
						has_moved[player_y][player_x][0] = 1;
						enemy_auto(mode);
					}
				}
				else{
					cout << "You've hit a wall!" << endl;
				}
			}
			else if (c == 'r'){
				c = new_semi_i_mode(mode);
				if (c == 'x'){
					cout << "You exited the game!" << endl;
					break;
				}
			}
			else if (c == 'b'){
				int prev_p_y = player_y, prev_p_x = player_x;
				move_p_e(has_moved[player_y][player_x][0], 0, ' ');
				has_moved[prev_p_y][prev_p_x][0] = -1;
				move_p_e(has_moved[enemy_y][enemy_x][1], 1, ' ');
			}
			else if (c == 'x'){
				cout << "You exited the game!" << endl;
				break;
			}
			if (isGameOver()){
				cout << "You hit an enemy! Game Over!" << endl;
				break;
			}
			if (player_x == initial_p_x&&player_y == initial_p_y){
				if (unsolvable()){
					cout << "The maze in unsolvable!" << endl;
					break;
				}
			}
		}
	}else{
		cout << "The maze in unsolvable!" << endl;
	}
}
void game(){
	char mode;
	read_store_maze("maze.txt");
	spawn_player();
	spawn_enemy();
	spawn_treasure();
	cout << "Intital Start With Randomly Spawned Player, Enemy, and Treasure" << endl;
	cout << "Penguin is the Player. Robot is the Enemy. Treasure Chest is the Treasure" << endl;
	print_maze();
	find_player_enemy_prize();
	make_window(sq*num_cols, sq*num_rows);
	draw_maze();
	cout << "Easy or Hard Mode?" << endl;
	cout << "Easy: Enemy Moves Randomly" << endl;
	cout << "Hard: Enemy Moves To Ambush the Player and Stand Guard in Front of the Treasure!" << endl;
	cout << "Enter E or H for respective modes." << endl;
	cin >> mode;
	cout << "w-UP" << endl;
	cout << "s-DOWN" << endl;
	cout << "a-LEFT" << endl;
	cout << "d-RIGHT" << endl;
	cout << "b-BACK" << endl;
	cout << "r-AUTOMATIC" << endl;
	cout << "m-MANUAL" << endl;
	cout << "x-EXIT" << endl;
	if (mode == 'E' || mode == 'e'){
		gameplay(0);
	}else if(mode=='H'||mode=='h'){
		gameplay(1);
	}
}
void main(){
	game();
}