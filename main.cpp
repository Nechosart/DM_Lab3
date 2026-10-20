#include <iostream>
#include <string>

using namespace std;

int main() {
	int a_size, b_size;
	float a[100];
	float b[100];

	cout << "Введіть розмір множини a: ";
	cin >> a_size;
	while (cin.fail() || a_size <= 0) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Неправильний ввід: ";
		cin >> a_size;
	}

	cout << "Введіть елементи множини a: ";
	for (int i = 0; i < a_size; i++) {
		cin >> a[i];
		while (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Неправильний ввід: ";
			cin >> a[i];
		}
	}

	cout << "Введіть розмір множини b: ";
	cin >> b_size;
	while (cin.fail() || b_size <= 0) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Неправильний ввід: ";
		cin >> b_size;
	}

	cout << "Введіть елементи множини b: ";
	for (int i = 0; i < b_size; i++) {
		cin >> b[i];
		while (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Неправильний ввід: ";
			cin >> b[i];
		}
	}

	cout << "Відношення a x b задане рівнянням: 5 * a - b > 3" << endl;

	int space_total = 0;
	int space_per_box[100];
	for (int j = 0; j < b_size; j++) {
		int value = to_string(b[j]).length() + 2;
		space_total += value + 1;
		space_per_box[j] = value;
	}

	int first_slot_max_size = 7;
	for (int i = 0; i < a_size; i++) {
		int value = to_string(a[i]).length() + 2;
		if (value > first_slot_max_size) {
			first_slot_max_size = value;
		}
	}
	space_total += first_slot_max_size + 2;

	// Printing first layer
	cout << string(space_total, '-') << endl
		<< "| a \\ b" << string(first_slot_max_size-6, ' ') << "|";
	for (int j = 0; j < b_size; j++) {
		cout << " " << to_string(b[j]) << " |";
	}


	bool values[100][100];
	// vertical
	for (int i = 0; i < a_size; i++) {
		cout << endl << string(space_total, '-') << endl
			<< "| " << to_string(a[i]) << " |";

		// horizontal
		for (int j = 0; j < b_size; j++) {
			bool value = (5 * a[i] - b[j]) > 3;
			values[i][j] = value;

			cout << string(space_per_box[j] / 2, ' ')
				<< value
				<< string(space_per_box[j] - space_per_box[j] / 2 - 1, ' ')
				<< "|";
		}
	}
	cout << endl << string(space_total, '-') << endl << endl;


	if (a_size != b_size) {
		cout << "Розміри матриць різні, тому класичні відношення не працюють" << endl;
	}
	else {
		bool is_reflexive = false;
		bool is_symetric = false;
		bool is_transitive = false;
		// Рефлексивне
		bool success = true;
		for (int i = 0; i < a_size; i++) {
			if (values[i][i] == false) {
				success = false;
				break;
			}
		}
		if (success) {
			is_reflexive = true;
			cout << "Відношення є рефлексивним" << endl;
		}
		else {
			success = true;
			for (int i = 0; i < a_size; i++) {
				if (values[i][i] == true) {
					success = false;
					break;
				}
			}
			if (success) {
				cout << "Відношення є антирефлексивним" << endl;
			}
			else {
				cout << "Відношення не є ні рефлексивним, ні антирефлексивним" << endl;
			}
		}

		// Симетричне
		success = true;
		for (int i = 0; i < a_size; i++) {
			for (int j = 0; j < b_size; j++) {
				if ((values[i][j] == true) && (values[j][i] == false)) {
					success = false;
					break;
				}
			}
		}
		if (success) {
			is_symetric = true;
			cout << "Відношення є симетричним" << endl;
		}
		else {
			success = true;
			for (int i = 0; i < a_size; i++) {
				for (int j = 0; j < b_size; j++) {
					if (values[i][j] == true && values[j][i] == true) {
						success = false;
						break;
					}
				}
			}

			if (success) {
				success = true;
				for (int i = 0; i < a_size; i++) {
					for (int j = 0; j < b_size; j++) {
						if (values[i][j] == values[j][i]) {
							success = false;
							break;
						}
					}
				}
				if (success) {
					cout << "Відношення є і антисиметричним, і асиметричним" << endl;
				}
				else {
					cout << "Відношення є антисиметричним" << endl;
				}
			}
			else {
				cout << "Відношення не є ні симетричним, ні антисиметричним" << endl;
			}
		}

		bool is_sets_equal = true;
		for (int i = 0; i < a_size; i++) {
			if (a[i] != b[i]) {
				is_sets_equal = false;
				break;
			}
		}
		
		if (is_sets_equal) {

			// Транзитивне
			success = true;
			for (int i = 0; i < a_size; i++) {
				for (int j = 0; j < b_size; j++) {
					if (values[i][j]) {
						for (int z = 0; z < a_size; z++) {
							if ((values[j][z] == true) && (values[i][z] == false)) {
								success = false;
								break;
							}
						}
					}
				}
			}
			if (success) {
				is_transitive = true;
				cout << "Відношення є транзитивне" << endl;
			}
			else {
				success = true;
				for (int i = 0; i < a_size; i++) {
					for (int j = 0; j < b_size; j++) {
						if (values[i][j]) {
							for (int z = 0; z < a_size; z++) {
								if ((values[j][z] == true) && (values[i][z] == true)) {
									success = false;
									break;
								}
							}
						}
					}
				}

				if (success) {
					cout << "Відношення є і атранзитивним, і антитранзитивним" << endl;
				}
				else {
					cout << "Відношення є атранзитивним" << endl;
				}
			}
		}

		if (is_reflexive && is_symetric && is_transitive) {
			cout << "Відношення є еквівалентним" << endl;
		} else {
			cout << "Відношення не є еквівалентним" << endl;
		}
	}


	return 0;
}
