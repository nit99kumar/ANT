#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class matrix
{
	public:
		int m, n;
		vector< vector<float> > mat;
		//empty constructor
		matrix();
		//taking user input
		void input(int, float, int);
		//subtraction of two matrices
		matrix operator-(matrix &);
		//multiplication of two matrices
		matrix operator*(matrix &);
		//inverse of a matirx
		matrix operator~();
		//displaying a matrix
		void display();
		//forming an identity matrix
		matrix identity(int);
		//get a column vector
		matrix get_column(int);
		void copy_mat(matrix);
		void rep_column(matrix &, int);
};

class matrix_3d
{
	public:
		int m, n, k;
		vector< vector< vector<float> > > mat;
		//input for 3d_matrix
		void input(int, int, int, int, float);
		matrix transform(int i);
};

matrix::matrix()
{
}

matrix matrix::operator-(matrix &B)
{
	int i, j;
	float sum;
	matrix A;// = new matrix();
	if(this->m != B.m)
	{
		cout << "error: matrices are not compatible for addition\n";
		exit(1);
	}
	for(i=0; i<this->m; i++)
	{
		vector<float> row;
		for(j=0; j<this->n; j++)
		{
			sum=0;
			sum = this->mat[i][j] - B.mat[i][j];
			row.push_back(sum);
		}
		A.mat.push_back(row);
	}
	A.m = this->m;
	A.n = this->n;
	return A;
}

matrix matrix::operator*(matrix &B)
{
	int i, j, k;
	float sum;
	matrix A; // = new matrix()
	if(this->n != B.m)
	{
		cout << "error: matrices are not compatible for multiplication\n";
		exit(1);
	}
	for(i=0; i<this->m; i++)
	{
		cout <"here\n";
		vector<float> row;
		for(j=0; j<B.n; j++)
		{
			sum = 0;
			for(k=0; k<B.m; k++)
				sum += this->mat[i][k] * B.mat[k][j];
			row.push_back(sum);
		}
		A.mat.push_back(row);
	}
	A.m = this->m;
	A.n = B.n;
	return A;
}

matrix matrix::identity(int dim)
{
	int i, j;
	matrix A;
	vector< vector<float> > a;
	for(i=0; i<dim; i++)
	{
		vector<float> row(dim);
		for(j=0; j<dim; j++)
		{
			if(i==j)
				row[j] = 1;
			else
				row[j] = 0;
		}
		a.push_back(row);
	}
	A.m = A.n = dim;
	A.mat = a;
	return A;
}

matrix matrix::get_column(int j)
{
	int i;
    matrix A;
	A.m = this->m;
    A.n = 1;
	for (i=0; i<this->m; i++)
	{
		vector<float> row(1);
		row[0] = this->mat[i][j];
		A.mat.push_back(row);
	}
    return A;
}

void matrix::rep_column(matrix &B, int j)
{
	int i;
	for(i=0; i<this->m; i++)
		this->mat[i][j] = B.mat[i][0];
}

void matrix::copy_mat(matrix B)
{
	int i, j;
	for(i=0; i<this->m; i++)
		this->mat[i] = B.mat[i];
}

matrix matrix::operator~()
{
	int i, j;
	matrix P, M_inv, res;
	float pivot;
	M_inv = M_inv.identity(this->m);
    for(i=0; i<this->m; i++)
	{
		matrix B = B.identity(this->m);
		P = this->get_column(i);
		res = M_inv * P;
		pivot = res.mat[i][0];
		for(j=0; j<this->m; j++)
		{
            if(j != i)
                res.mat[j][0] = -res.mat[j][0]/pivot;
            else
                res.mat[j][0] = 1/pivot;
        }
		B.rep_column(res, i);
		res = B * M_inv;
		M_inv.copy_mat(res);
    }
    return M_inv;
}

void matrix::input(int choice, float h, int t)
{
	vector<float> row(2);
	if(choice == 1)
	{
		row[0] = -1; row[1] = -(h/2);
		this->mat.push_back(row);
		row[0] = 0; row[1] = (1/(h*h)) + (5/(2*h));
		this->mat.push_back(row);
	}
	if(choice == 2)
	{
		row[0] = 1; row[1] = -(h/2);
		this->mat.push_back(row);
		row[0] = -4; row[1] = -(2/(h*h)) + 8;
		this->mat.push_back(row);
	}
	if(choice == 3)
	{
		row[0] = 0; row[1] = 0;
		this->mat.push_back(row);
		row[0] = 0; row[1] = (1/(h*h)) - (5/(2*h));
		this->mat.push_back(row);
	}
	if(choice == 4)
	{
		if(t == 0)
		{
			vector<float> row1(1);
			row1[0] = 1.75 + (2*h);
			this->mat.push_back(row1);
			row1[0] = 1-((4/(h*h)) + (10/h));
			this->mat.push_back(row1);
		}
		if(t == ((1/h)-2))
		{
			vector<float> row1(1);
			row1[0] = 0;
			this->mat.push_back(row1);
			row1[0] = 1 - 39.663*((1/(h*h)) - (5/(2*h)));
			this->mat.push_back(row1);
		}
		else
		{
			vector<float> row1(1);
			row1[0] = 0;
			this->mat.push_back(row1);
			row1[0] = 1;
			this->mat.push_back(row1);
		}

	}
}

void matrix::display()
{
	int i, j;
	cout << endl;
	for(i=0; i<this->m; i++)
	{
		for(j=0; j<this->n; j++)
			cout << this->mat[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

matrix matrix_3d::transform(int i)
{
	matrix A;
	A.mat = this->mat[i];
	A.m = this->n;
	A.n = this->k;
	return A;
}

void matrix_3d::input(int n, int row, int col, int choice, float h)
{
	int i;
	for(i=0; i<n; i++)
	{
		matrix A;
		A.m = row;
		A.n = col;
		//cout << "enter the " << i+1 <<"th matrix in this series\n";
		A.input(choice, h, i);
		this->mat.push_back(A.mat);
	}
	this->m = n;
	this->n = row;
	this->k = col;
}

int main()
{
	matrix V, W, X, Y, Z;
	int i, j, k, row, col, n;//n -> dimension of the block tridiagonal matrix
	float h;//h -> step size
	cout << "enter the step size: ";
	cin >> h;
	n = (1/h)-1;
	row = 2; col = 2;
	
	matrix_3d A, B, C, D, B1, C1, D1, X1;
	A.input(n, row, col, 1, h);
	B.input(n, row, col, 2, h);
	C.input(n, row, col, 3, h);
	D.input(n, row, 1, 4, h);
	
	//thomas algorithm for block tri-diagonal matrix system
	W = B.transform(0);
	W = ~W;
	X = C.transform(0);
	X = W * X;
	C1.mat.push_back(X.mat);C1.m = 1; C1.n = row; C1.k = col;
	X = D.transform(0);
	X = W * X;
	D1.mat.push_back(X.mat);D1.m = 1; D1.n = row; D1.k = 1;
	for(i=1; i<n; i++)
	{
		//1st equation
		W = A.transform(i);
		X = C1.transform(i-1);
		Y = W * X;
		Z = B.transform(i);
		Z = Z - Y;
		B1.mat.push_back(Z.mat);B1.m = i; B1.n = row; B1.k = col;
		//2nd equation
		W = B1.transform(i-1);//'i-1' as it is getting pushed for the first time
		W = ~W;
		X = C.transform(i);
		Y = W * X;
		C1.mat.push_back(Y.mat);C1.m = i+1; C1.n = row; C1.k = col;
		//3rd equation
		X = D1.transform(i-1);
		Y = A.transform(i);
		Z = Y * X;
		V = D.transform(i);
		V = V - Z;
		W = W * V;
		D1.mat.push_back(W.mat);D1.m = i+1; D1.n = row; D1.k = 1;
	}
	
	cout << "result\n";
	//displaying the result
	X = D1.transform(n-1);
	X1.mat.push_back(X.mat);X1.m = 1; X1.n = row; X1.k = 1;
	for(i=n-2; i>=0; i--)
	{
		Y = C1.transform(i);
		Z = Y * X;
		W = D1.transform(i);
		W = W - Z;
		X1.mat.push_back(W.mat);X1.m = n-i; X1.n = row; X1.k = 1;
		X = X1.transform(n-i-1);
	}

	for(i=n-1; i>=0; i--)
	{
		X = X1.transform(i);
		cout << h*(n-i) << " -> " << X.mat[0][0] << endl;
	}
	return 0;
}