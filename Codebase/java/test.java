public enum Test {
    WEST("Miss Gulch"),
    NORTH("Glinda"),
    EAST("Wicked"),
    SOUTH("Good");

    private String description;
    private Test(String description) {
        this.description = description;
    }
    public String getDescription() { return description; }

    public static void main(String[] args) {
        for (Test witch : Test.values()) {
            System.out.println(witch + ": " + witch.getDescription());
        }
    }
}
