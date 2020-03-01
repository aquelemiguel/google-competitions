#include <bits/stdc++.h>
using namespace std;

class Book {
    public:
    int id, points;

    Book(int id, int points) {
        this->id = id;
        this->points = points;
    }

    bool operator <(Book const& a) {
        return this->points > a.points;
    }
};

class Library {
    public:
    int id, signup, shipPerDay;
    double score;
    vector<Book> books;

    Library(int id, int signup, int shipPerDay) {
        this->id = id;
        this->signup = signup;
        this->shipPerDay = shipPerDay;
    }

    void addBook(Book book) {
        books.push_back(book);
    }

    void computeScore(int nLibraries, int book_freqs[], double weightSignup, double weightBooks) {
        double score = 0.0;

        for (int i = 0; i < books.size(); i++) {
            score += ((double)books[i].points - (double)books[i].points*((double)book_freqs[books[i].id] / (double)nLibraries)); 
        }

        double part1 = (signup/100000.0) * weightSignup;
        double part2 = (score)/1000.0 * weightBooks;

        // cout << part1 << " " << part2 << endl;

        this->score = part2 - part1;
    }

    bool operator <(Library const& a) {
        return this->score > a.score;
    }
};


vector<int> split_string(string str, char delim) {
    vector<int> arr;
    replace(str.begin(), str.end(), delim, ' ');
    stringstream ss(str);

    int temp;
    while (ss >> temp) arr.push_back(temp);
    return arr;
}

int solve(string filename) {
    string s;

    ifstream infile("input/" + filename + ".txt");

    vector<Library> libraries;

    getline(infile, s);
    vector<int> general = split_string(s, ' ');

    getline(infile, s);
    vector<int> book_scores = split_string(s, ' ');

    int book_freqs[general[0]];
    memset(book_freqs, 0, sizeof(int) * general[0]);
    
    // Create printed array
    int printed[general[0]]; 
    memset(printed, -1, sizeof(int) * general[0]);
    
    for (int i = 0; i < general[1]; i++) {
        getline(infile, s);
        vector<int> lib_line = split_string(s, ' ');

        Library lib = Library(i, lib_line[1], lib_line[2]);

        getline(infile, s);
        vector<int> book_line = split_string(s, ' ');
        
        for (int j = 0; j < book_line.size(); j++) {
            lib.addBook(Book(book_line[j], book_scores[book_line[j]]));
            book_freqs[book_line[j]]++;
        }

        libraries.push_back(lib);
    }

    for (int i = 0; i < libraries.size(); i++) {
        sort(libraries[i].books.begin(), libraries[i].books.end());

        libraries[i].computeScore(libraries.size(), book_freqs, 0.6, 0.4); //tempo, pontos
        //cout << libraries[i].score << endl;
    }

    sort(libraries.begin(), libraries.end());

    /*
    for (int i = 0; i < libraries.size(); i++) {
        cout << libraries[i].id << " " << libraries[i].signup << " " << libraries[i].shipPerDay << endl;
        
        for (Book book : libraries[i].books) {
            cout << book.id << " " << book.points << endl;
        }
    }
    */
    

    for (int i = 0; i < libraries.size(); i++) {
        for (Book b : libraries[i].books) {
            if (printed[b.id] == -1) {
                printed[b.id] = libraries[i].id;
            }
        }
    }

    // Print stuff

    for (int sol = 0; sol < 6; sol++) {
        ofstream output("output/" + filename + "_out.txt");

        int library_count = libraries.size();
        string result = "";
        //output << libraries.size() << endl;


        for (int i = 0; i < libraries.size(); i++) {
            bool hasBooks = false;

            int ct = count(printed, printed + general[0], libraries[i].id);

            if (ct != 0) {
                result += (to_string(libraries[i].id) + " " + to_string(ct) + "\n");
            }

            for (Book b : libraries[i].books) {
                if (printed[b.id] == libraries[i].id) {
                    result += (to_string(b.id) + " ");
                    hasBooks = true;
                }
            }

            if (!hasBooks) {
                library_count--;
            } else {
                result += "\n";
            }
        }

        result = to_string(library_count) + "\n" + result;
        output << result;
        output.close();

    }
    cout << "DONE PRINTING " << filename << ".txt" << endl;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie();

    string files[6] = {"a", "b", "c", "d", "e", "f"};

    for (int i = 0; i < 6; i++) {
        solve(files[i]);
    }
}

