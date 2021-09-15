#include <iostream>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

using namespace std;

fraction_builder(int *num, int *den, char string[20]){ // stdlib needed
	char a[10], b[10];
	int len, i, j, n, d;
	
	len = strlen(string);
	
	for(i = 0; i < len; i++){
		if(string[i] == '/') break;
		else a[i] = string[i];
	}
	i++;
	len -= i;
	for(j = 0; j < len; j++){
		b[j] = string[i];
		i++;
	}
	
	n = atoi(a);
	if(j == 0){
		d = 1;
	}
	else d = atoi(b);
	
	
	*num = n;
	*den = d;
	
}

int lcm(int n1, int n2){
    int remnant, a, b;

    a = n1;
    b = n2;

    do {
        remnant = a % b;

        a = b;
        b = remnant;

    } while(remnant != 0);

    return (n1 * n2) / a;
}

add_fraction(int *numerator, int *denominator, int nb, int db){
	int na, da, m;
	
	na = *numerator;
	da = *denominator;
	m = lcm(da, db);
	
	na *= (m / da);
	nb *= (m / db);
	
	na += nb;
	*numerator = na;
	*denominator = m;
}

simplify_fraction(int *n, int *d){
	int num, den, signal_n = 1, signal_d = 1;
	int num_f = 1, den_f = 1;
	int i, x = 3, list_num[20], list_den[20], j = 0, count_num = 0, count_den = 0;
	
	num = *n;
	den = *d;

	if(num < 0){
		num *= -1;
		signal_n = -1;
	}
	if(den < 0){
		den *= -1;
		signal_d = -1;
	}

	while(num > 1){
		while(num % 2 == 0){
			list_num[j] = 2;
			j++;
			num = num / 2;
			count_num++;
		}
		if(num % x == 0){
			list_num[j] = x;
			j++;
			num = num / x;
			count_num++;
		}
		else x += 2;
	}
	j = 0; x = 3;
	while(den > 1){
		while(den % 2 == 0){
			list_den[j] = 2;
			j++;
			den = den / 2;
			count_den++;
		}
		if(den % x == 0){
			list_den[j] = x;
			j++;
			den = den / x;
			count_den++;
		}
		else x += 2;
	}
	
	for(i = 0; i < count_num; i++){
		for(j = 0; j < count_den; j++){
			if(list_num[i] == list_den[j]){
				list_num[i] = 1;
				list_den[j] = 1;
				break;
			}
		}
	}
	
	if(num == 0) num_f = 0;
	else{
		for(i = 0; i < count_num; i++){
			num_f *= list_num[i];
		}
		
		for(i = 0; i < count_den; i++){
			den_f *= list_den[i];
		}
	}
	
	if(signal_n == signal_d){
		signal_n = 1;
		signal_d = 1;
	}
	
	*n = signal_n*num_f;
	*d = signal_d*den_f;
	
}

int superior_triangular_verifier(int matrix[10][10][2], int range){
	int i, k, quality = TRUE;
	
	for(i = 0; i < range; i++){
		if(matrix[i][i][0] != 0){
			for(k = i+1; k < range; k++){
				if(matrix[k][i][0] != 0){
					quality = FALSE; break;
				}
			}
		}
		else{
			quality = FALSE; break;
		}
	}
	return quality;
}

main(){
	int range, i, j = 0, option, l1, l2, signal = 1, count = 1, sus;
	int matrix[10][10][2];
	int determinant_num = 1, determinant_den = 1, multiplier_num = 1, multiplier_den = 1, f_multiplier_num = 1, f_multiplier_den = 1;
	char string[20];
	
	cout << "=============================\n";
	cout << "        Scaling tool\n";
	cout << "=============================\n";
	cout << "\nMatrix range: ";
	cin >> range;
	cout << "\nType the elements in reading order:\n";
	
	for(i = 0; i < range; i++){
        cout << "\nRow " << i+1 << ":\n";
        for(j = 0; j < range; j++){
        	cin >> string;
        	fraction_builder(&matrix[i][j][0], &matrix[i][j][1], string);
			}
    }
    
    while(not superior_triangular_verifier(matrix, range)){
    	cout << "\n=============================\n";
    	cout << "\nMatrix(" << count << "):\n";
		for(i = 0; i < range; i++){
        	cout << endl;
        	for(j = 0; j < range; j++){
        		simplify_fraction(&matrix[i][j][0], &matrix[i][j][1]);
        		if(matrix[i][j][1] == 1){
        			cout << matrix[i][j][0] << "     ";
				}
				else cout << matrix[i][j][0] << "/" << matrix[i][j][1] << "   ";
        	}
  		}
  		count++;
  		
    	cout << "\n\nSelect the operation:\n";
    	cout << "(1) to swap lines, (2) to multiply the line, (3) to replace the line: ";
    	cin >> option;
    	
    	switch(option){
    		case 1: // swap lines
    			
    			cout << "\nSelect the lines to swap: ";
    			cin >> l1;
    			cin >> l2;
    			l1 += -1;
    			l2 += -1;
    			
    			for(j = 0; j < range; j++){
    				i = matrix[l1][j][0];
    				matrix[l1][j][0] = matrix[l2][j][0];
    				matrix[l2][j][0] = i;
    				i = matrix[l1][j][1];
    				matrix[l1][j][1] = matrix[l2][j][1];
    				matrix[l2][j][1] = i;
				}
				signal *= -1;
    			
    			break;
    		case 2: // multiply line
    			
    			cout << "\nSelect the line to multiply: ";
    			cin >> l1;
    			l1 += -1;
    			cout << "\nType the multiplier: ";
    			cin >> string;
    			fraction_builder(&multiplier_num, &multiplier_den, string);
    			f_multiplier_num *= multiplier_num;
    			f_multiplier_den *= multiplier_den;
    			
    			for(j = 0; j < range; j++){
    				matrix[l1][j][0] *= multiplier_num;
				}
				for(j = 0; j < range; j++){
    				matrix[l1][j][1] *= multiplier_den;
				}

    			break;
    		case 3: // replace line
    			
				cout << "\nSelect the line to multiply: ";
				cin >> l1;
				l1 += -1;
				cout << "\nType the multiplier: ";
				cin >> string;
				fraction_builder(&multiplier_num, &multiplier_den, string);
				cout << "\nSelect the line to add and replace: ";
				cin >> l2;
				l2 += -1;
				
				for(j = 0; j < range; j++){
					add_fraction(&matrix[l2][j][0], &matrix[l2][j][1], multiplier_num*matrix[l1][j][0], multiplier_den*matrix[l1][j][1]);
				}
				
    			break;
		}
	}
	
	cout << "\n\n=============================\n\n";
    cout << "Superior triangular Matrix(" << count << "):\n";
    
	for(i = 0; i < range; i++){
       	cout << endl;
        for(j = 0; j < range; j++){
           	if(matrix[i][j][1] == 1){
        		cout << matrix[i][j][0] << "     ";
			}
			else cout << matrix[i][j][0] << "/" << matrix[i][j][1] << "   ";
        }
  	}
  	
	for(i = 0; i < range; i++){
		determinant_num *= matrix[i][i][0];
	}
	for(i = 0; i < range; i++){
		determinant_den *= matrix[i][i][1];
	}
	
	simplify_fraction(&determinant_num, &determinant_den);
	
	if(determinant_den == 1) cout << "\n\nMatrix(" << count << ") Determinant: " << determinant_num;
	else cout << "\n\nMatrix(" << count << ") Determinant: " << determinant_num << "/" << determinant_den;
	
	determinant_num *= signal * f_multiplier_den;
	determinant_den *= f_multiplier_num;
	
	simplify_fraction(&determinant_num, &determinant_den);
	
	if(determinant_den == 1) cout << "\n\nOriginal matrix Determinant: " << determinant_num;
	else cout << "\n\nOriginal matrix Determinant: " << determinant_num << "/" << determinant_den;
	cout << "\n\n=============================\n\n";
	cin >> sus;
}

