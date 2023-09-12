// once DOM is loaded, add an event listener to the form and when is submitted
// take the input value and show a message
document.addEventListener('DOMContentLoaded', () => {
    document.querySelector('form').addEventListener('submit', (event) => {
        let name = document.querySelector('#name').value;
        alert('hello, ' + name);
        event.preventDefault();
    });
});