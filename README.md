# BuBa_engine

## Roadmap Features 
### 0.2.0 [Not Started]
- [ ] Assign amout to territory
- [ ] Synchro with online bank
- [ ] Automatic category assignement for transaction

### 0.1.0 [In Progress]
- [x] Create/Open Buba project
- [x] Import OFX (Transactions, Account, Bank)
- [x] Set bank name interface
- [x] Set account name interface
- [ ] List all transactions
- [ ] Assign category to operation
- [ ] Display monthly static of category percent

#### Dev
- [ ] Add License file
- [ ] Update all header file doxygen header
- [ ] Add unit test
- [ ] Add logging mechanism
- [ ] Add control on column name when SELECT
- [x] Rename table operation to transaction

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
