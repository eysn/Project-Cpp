# Project-Cpp

## Overview

This Hotel Management System is a C++ project designed to manage hotel bookings, guest accounts, and financial transactions. It allows users to book rooms, manage their accounts, and process payments using a microfinance system. The project is structured with two main components: bank operations and hotel management functionalities.

## Features

- **Account Management**: Create and manage guest accounts with basic information.
- **Room Booking**: View available rooms and book them for a specified number of nights.
- **Payment Processing**: Make payments using a voucher system or through bank transfers.
- **Reservation Cancellation**: Cancel bookings and process refunds.
- **Data Persistence**: Store account and room information in CSV files for data persistence.

## Components

1. **bank.cpp**: Handles bank account operations, including:
   - Creating accounts
   - Depositing, withdrawing, and transferring money
   - Paying for hotel bookings using vouchers

2. **hotel.cpp**: Manages hotel operations, including:
   - Initializing and displaying available rooms
   - Booking rooms for guests
   - Canceling reservations
   - Reading and writing account information from/to CSV files

3. **CSV Files**:
   - **account information.csv**: Stores guest account details, including names, email, phone number, and account balances.
   - **room information.csv**: Stores room details, including voucher codes, total prices, payment status, and room numbers.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++, clang++, codeblocks)
- Standard C++ libraries

### Installation

1. Clone the repository:
   ```bash
git clone https://github.com/eysn/Project-Cpp.git
cd Project-Cpp
