#include "ch17.h"

#define FILE_COL 256

int getCol(char* str) {
	int col = 0;
	char s[FILE_COL] = { 0 };
	strcpy(s, str);

	char* token = strtok(s, "\t");
	while (token != NULL) {
		col++;
		token = strtok(NULL, "\t");
	}
	return col;
}

Matrix* reatMatFile(char* fileName) {
	FILE* fp = fopen(fileName, "r");
	if (!fp) {
		printf("文件打开失败\n");
		return NULL;
	}

	Matrix* m = creatMatrix(0, 0);
	int row = 0;
	int col = 0;
	char buffer[FILE_COL] = { 0 };

	fgets(buffer, FILE_COL, fp);
	
	col = getCol(buffer);
	if (col) row = 1;

	m->col = col;
	m->row = row;
	m->mat = (double**)malloc(sizeof(double*) * row);
	m->mat[0] = (double*)malloc(sizeof(double) * col);
	
	char* token = strtok(buffer, "\t");
	for (int i = 0; i < m->col; i++) {
		if (sscanf(token, "%lf", &(m->mat[0][i])) != 1) {
			m->mat[0][i] = 0.0;
		}
		if (token != NULL) {
			token = strtok(NULL, "\t");
		}
	}

	while (fgets(buffer, FILE_COL, fp)) {
		m->mat = (double**)realloc(m->mat, sizeof(double*) * (m->row + 1));
		m->mat[m->row] = (double*)malloc(sizeof(double) * m->col);

		token = strtok(buffer, "\t");
		for (int i = 0; i < m->col; i++) {
			if (sscanf(token, "%lf", &m->mat[m->row][i]) != 1) {
				m->mat[m->row][i] = 0.0;
			}
			if (token != NULL) {
				token = strtok(NULL, "\t");
			}
		}

		m->row++;
	}
	fclose(fp);
	return m;
}