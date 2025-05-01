// Store your processes data
let processes = [
    { name: 'P1', burstTime: 4 },
    { name: 'P2', burstTime: 3 },
    { name: 'P3', burstTime: 2 },
    { name: 'P4', burstTime: 1 }
];

// Example FCFS Scheduling
function runFCFS() {
    // Simulate First-Come, First-Served (FCFS)
    document.getElementById("outputText").innerHTML = "Running First-Come, First-Served (FCFS) Scheduling Algorithm...";

    // Assuming FCFS, we calculate the start time and end time for each process
    let startTime = 0;
    let endTime = 0;
    let labels = [];
    let data = [];

    // Generate data for chart
    processes.forEach(process => {
        startTime = endTime;
        endTime = startTime + process.burstTime;
        labels.push(process.name);
        data.push(process.burstTime);
    });

    // Call the function to update the chart with the FCFS result
    updateChart(labels, data);
}

// Update the chart with new data
function updateChart(labels, data) {
    const ctx = document.getElementById('ganttChart').getContext('2d');

    // Destroy the old chart if it exists (to prevent multiple charts from stacking)
    if (window.chart) {
        window.chart.destroy();
    }

    // Create a new chart
    window.chart = new Chart(ctx, {
        type: 'bar',
        data: {
            labels: labels,  // Process names (P1, P2, etc.)
            datasets: [{
                label: 'Process Burst Time (Execution Time)',
                data: data,  // Burst time of each process
                backgroundColor: 'rgba(54, 162, 235, 0.5)',
                borderColor: 'rgba(54, 162, 235, 1)',
                borderWidth: 1
            }]
        },
        options: {
            responsive: true,
            scales: {
                y: {
                    beginAtZero: true
                }
            }
        }
    });
}

// The same concept can be applied to other scheduling algorithms like SJF, RR, etc.
