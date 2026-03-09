# IntraProcure

A procurement and internal resource management application designed for organizations to manage purchasing workflows, users, and database-driven operations.

---

## System Requirements

### Operating System
- Windows 10 (64-bit)
- Windows 11 (64-bit)

### Required Frameworks and Runtimes
- Microsoft .NET Framework 4.8.1
- Microsoft Visual C++ Redistributable 2015–2022 (x64)

### Development Tools (Required only for compiling the source code)
- Microsoft Visual Studio 2022 with the following workloads installed:
  - Desktop development with C++
  - .NET desktop development
  - MSVC v143 build tools
  - Windows 10/11 SDK

### Database Requirements
- Microsoft SQL Server 2016 or later
- SQL Server Express OR Azure SQL Database

Additional requirements:
- SQL Authentication must be enabled
- Database tables must be created using the provided SQL script
- The connection string is located in:

IntraProcure/Config.h

---

## How to Compile the Source Code

1. Open Visual Studio 2022.
2. Open the solution file:

IntraProcure.sln

3. Set the build configuration:

Configuration: Debug or Release  
Platform: x64

4. In Visual Studio select:

Build → Rebuild Solution

5. After successful compilation, the executable will be located in:

Development build:
IntraProcure/x64/Debug/IntraProcure.exe

Release build:
IntraProcure/x64/Release/IntraProcure.exe

---

## How to Run the Application

### 1. Install Required Runtimes

Ensure the following are installed:

- .NET Framework 4.8.1
- Visual C++ Redistributable 2015–2022 (x64)

---

### 2. Prepare the Database

1. Open SQL Server Management Studio (SSMS).
2. Create a new database named:

IntraProcure

3. Run the provided SQL script to:
   - Create database tables
   - Insert base data

4. Create a SQL Authentication user with read/write permissions.

5. Ensure the SQL Server firewall allows client connections.

---

### 3. Configure the Application

Open the configuration file:

IntraProcure/Config.h

Update the `GetConnectionString()` function with:

- Server address
- Database name
- SQL username
- SQL password

---

### 4. Run the Application

Double-click:

IntraProcure.exe

---

### 5. Login

Use an existing account stored in the database.

Available roles may include:
- Admin
- Manager
- Employee

Access permissions depend on the configured user role.

---

End of README
