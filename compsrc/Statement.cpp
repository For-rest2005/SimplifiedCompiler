#include "Statement.h"

Statement::~Statement(){delete next;}
Statement::Statement(Statement *_next):next(_next){}