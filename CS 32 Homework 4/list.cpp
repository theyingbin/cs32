void listAll(const MenuItem* m, string path) // two-parameter overload
{
	if (path.length() != 0){
		path = path + '/' + m->name();
	}
	else{
		path = m->name();
	}
	if (path.length() != 0){
		cout << path << endl;
	}
	if (m->menuItems() == NULL){
		return;
	}
	else{
		const vector<MenuItem*>* items = m->menuItems();
		for (size_t i = 0; i < items->size(); i++){
			listAll((*items)[i], path);
		}
	}
}