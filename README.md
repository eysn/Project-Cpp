# Project-Cpp

## Overview

This is a Hotel Management System implemented in C++. The system is designed to manage hotel bookings, guest accounts, and financial transactions. Users can book rooms, manage their accounts, and process payments using a microfinance system.

## Features

- **Account Management**: Create and manage guest accounts with personal information.
- **Room Booking**: View available rooms and book them for a specified number of nights.
- **Payment Processing**: Make payments using a voucher system or through bank transfers.
- **Reservation Cancellation**: Cancel bookings and process refunds.
- **Data Persistence**: Store account and room information in CSV files.

## Components

1. **bank.cpp**: Manages bank account operations, including:
   - Creating accounts
   - Depositing, withdrawing, and transferring money
   - Paying for hotel bookings using vouchers

2. **hotel.cpp**: Handles hotel operations, including:
   - Initializing and displaying available rooms
   - Booking rooms for guests
   - Canceling reservations
   - Reading and writing account information from/to CSV files

3. **CSV Files**:
   - **account information.csv**: Stores guest account details (names, email, phone number, account balances).
   - **room information.csv**: Stores room details (voucher codes, total prices, payment status, room numbers).

## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++, clang++, Code::Blocks)
- Standard C++ libraries

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/eysn/Project-Cpp.git
   cd Project-Cpp
