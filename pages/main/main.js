async function fetchData() {
	try {
		const response = await fetch('http://localhost:3000/api/data');
		const data = await response.json();
		document.getElementById('data-container').innerText = JSON.stringify(data);
	} catch (error) {
		console.error('Error while retrieving data:', error);
	}
	}
