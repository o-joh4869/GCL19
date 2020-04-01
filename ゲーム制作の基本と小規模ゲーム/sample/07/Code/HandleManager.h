#pragma once
enum HandleName {
	GRHANDLE_TITLE,
	//...
	HANDLE_SIZE
};


class HandleManager {
public:
	HandleManager();
private:
	int mHandle[HANDLE_SIZE];
public:
	void load();
	const int &operator[](const HandleName &handleName) {
		return mHandle[handleName];
	}
};

extern HandleManager gHandle;