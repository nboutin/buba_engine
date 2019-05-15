# BuBa_engine

## Roadmap Features 
### 0.3.0 [Not Started]
- [ ] Define goals list

### 0.2.0 [Not Started]
- [ ] Assign amout to territory
- [ ] Synchro with online bank
- [ ] Automatic category assignement for transaction
- [ ] Check account balance imported against computed

### 0.1.0 [In Progress]
- [x] Create/Open Buba project
- [x] Import OFX (Transactions, Account, Bank)
- [x] Set bank name interface
- [x] Set account name interface
- [x] List all transactions
- [x] Assign label to transaction
- [x] Assign category to label
- [x] Import account balance from OFX
- [ ] Get monthly spending of category percent and value
- [ ] Get monthly average income

#### Dev
- [x] Add print account balance
- [x] Add logging mechanism
- [x] Add project close interface
- [x] Rename table operation to transaction
- [x] Check return function of libofx
- [ ] Add default special label (movement)
- [ ] Add default standard label (savings)
- [ ] Add default special category (income) (check that value is positive)
- [ ] Add License file
- [ ] Update all header file doxygen header
- [ ] Add unit test
- [ ] Add control on column name when SELECT
- [ ] Create table if not exist

## How To
### Configure
```sh
cmake -H. -Bbuild
```

### Build
```sh
cmake --build build -- -j 4
```

### Install
```sh
sudo cmake --build build --target install
```

### Test
```sh
cmake --build build --target test
```
