#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

int Account::getNbAccounts() {
	return (_nbAccounts);
}

int Account::getTotalAmount( void ) {
	return (_totalAmount);
};

int Account::getNbDeposits( void ) {
	return (_totalNbDeposits);
};

int Account::getNbWithdrawals( void ) {
	return (_totalNbWithdrawals);
};

void Account::displayAccountsInfos( void ) {
	_displayTimestamp();
	std::cout << "accounts:" << Account::getNbAccounts() << ";";
	std::cout << "total:" << Account::getTotalAmount() << ";";
	std::cout << "deposits:" << Account::getNbDeposits() << ";";
	std::cout << "withdrawals:" << Account::getNbWithdrawals() << std::endl;
};

Account::Account() {
	this->_accountIndex = _nbAccounts;

	_displayTimestamp();
	std::cout << "index:" <<_accountIndex << ";";

	_nbAccounts++;
	_totalAmount++;
}

Account::Account( int initial_deposit ) {
	this->_accountIndex = _nbAccounts;
	this->_amount = initial_deposit;

	_displayTimestamp();
	std::cout << "index:" <<_accountIndex << ";";
	std::cout << "amount:" << this->_amount << ";" << "created" << std::endl;

	_nbAccounts++;
	_totalAmount += initial_deposit;
}

Account::~Account( void ) {
	_displayTimestamp();
	std::cout << "index:" <<_accountIndex << ";";
	std::cout << "amount:" << this->_amount << ";" << "closed" << std::endl;

	_nbAccounts--;
}

void	Account::makeDeposit( int deposit ) {
	_displayTimestamp();
	this->_nbDeposits++;
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "amount:" << this->_amount << ";";
	std::cout << "deposit:" << deposit << ";";
	std::cout << "nb_deposits:" << this->_nbDeposits << std::endl;
	this->_amount += deposit;
	_totalAmount += deposit;
};

bool	Account::makeWithdrawal( int withdrawal ) {
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "p_amount:" << this->_amount << ";";
	std::cout << "withdrawal:" << withdrawal << ";";

	if (checkAmount() >= withdrawal) {
		this->_amount -= withdrawal;
		_totalAmount -= withdrawal;
		this->_nbWithdrawals++;
		std::cout << "amount:" << this->_amount << ";";
		std::cout << "nb_withdrawals:" << this->_nbWithdrawals << std::endl;
		return (true);
	}
	else {
		std::cout << "withdrawal:refused" << std::endl;
		return (false);
	}
};

int		Account::checkAmount( void ) const {
	return (this->_amount);
};

void	Account::displayStatus( void ) const {
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "amount:" << this->_amount << ";";
	std::cout << "deposits:" << this->_nbDeposits << ";";
	std::cout << "withdrawals:" << this->_nbWithdrawals << std::endl;
};

void	Account::_displayTimestamp( void ) {
	std::time_t timestamp;

	timestamp = time(NULL);
	std::tm* t;
	t = localtime(&timestamp);
	std::cout << "[" << t->tm_year + 1900 << std::setw(2) << std::setfill('0') << t->tm_mon + 1 << t->tm_mday << "_";
	std::cout << t->tm_hour << t->tm_min << t->tm_sec << "]" << " ";
};